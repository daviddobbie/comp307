using namespace std;

#include "Population.h"

#include "Fitness.h"

#include "GeneticProgram.h"

#include "NodeSet.h"
#include "ProgramGenerator.h"

#include "PlusDouble.h"
#include "MinusDouble.h"
#include "MultDouble.h"
#include "DivideDouble.h"

#include "XDouble.h"
#include "RandDouble.h"

#include "ReturnDouble.h"

#include "SymbolicFitness.h"

#include "GPConfig.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

#ifdef MPI_ENABLED
#include "mpi.h"
#endif

int main (int argc, char* argv[])
{
   GPConfig symConfig;
   
   int Pop_Size = 5000;
   int Initial_Popsize = 5000;
   
   int processID = 0; // for MPI processing, sets the processor ID to 0;

#ifdef MPI_ENABLED	//MPI initialization if -D MPI_ENABLED is true
	int processSize = 0; 
    MPI_Init (&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &processSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &processID);
	if(processID != 0)
	{Pop_Size = 2; Initial_Popsize = 2;}
#endif
	
   //Declare a population, giving the size and a log file name
   Population pop(Pop_Size, Initial_Popsize,  "run-log.txt", &symConfig);
   string s1;
  
   //Set the rates of mutation etc 
   pop.setMutationRate(0.28);
   pop.setCrossoverRate(0.70);
   pop.setElitismRate(0.02);

   //Set the return type for our programs
   pop.setReturnType(ReturnDouble::TYPENUM);

   //Set the depth limit for the system
   symConfig.maxDepth = 6;
   symConfig.minDepth = 1;

   //Set the depth limit for the population
   pop.setDepthLimit(symConfig.maxDepth);
   pop.setMinDepth(symConfig.minDepth);

   //Write out the population every N generations
   pop.setLogFrequency(100);

#ifdef UNIX
   pop.compressGenerationFiles(true);
#endif

   //Do the default initialisation of the configuration
   symConfig.defaultInit();

   //Add the terminals we need 
   symConfig.termSet.addNodeToSet(ReturnDouble::TYPENUM, RandDouble::generate);
   symConfig.termSet.addNodeToSet(ReturnDouble::TYPENUM, XDouble::generate);

   //Add the functions we need
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, PlusDouble::generate);
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, MinusDouble::generate);
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, MultDouble::generate);
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, DivideDouble::generate);

   //Create the program generator
   symConfig.programGenerator = new ProgramGenerator(&symConfig);

   //Set the fitness class to be used
   symConfig.fitnessObject = new SymbolicFitness(&symConfig);

   //Initialise the fitness 
   symConfig.fitnessObject->initFitness();
  
#ifdef MPI_ENABLED // MPI setup/allocation of slave processors
    if(processID != 0)
    {
		pop.generateInitialPopulation();
		SymbolicFitness * classPointer = dynamic_cast<SymbolicFitness*>(symConfig.fitnessObject);
		classPointer->slaveProcess(pop.getIndividual(0));
		MPI_Finalize();
		return 0;
    }
#endif  
  
   if (argc == 2)
   { 
      //If there is one command line argument assume its a pop
      //file name
      //Reading a population from a file
      try
      {
         pop.readFromFile(argv[1]);
      }
      catch(const string & err)
      {
         cerr << err << endl;
         cerr << "Exiting" << endl;
         exit(1);
      }
   }
   else
   {
      pop.generateInitialPopulation();
   }

   try
   {
      string str1;
   
      /*Do 1000 generations, returns true if solution is found
        (see fitness class*/
      if (pop.evolve(5000))
      {
         cout << "Found solution" << endl;
      }
      else
      {
         cout << "Didn't find solution" << endl;
      }

      pop.getBest()->print(str1);
      cout << "Best program" << endl
           << "Fitness " << pop.getBest()->getFitness() << endl
           << str1 << endl;
   }
   catch (const string & s)
   {
      cerr << s <<endl;
      cerr << "Exiting" << endl;
      exit(1);
   }


   //The following code executes the best program on the training data
   //and outputs the results of the execution to the file results.txt 
   cout << "Writing results to results.txt..." << endl;

   dynamic_cast<SymbolicFitness *>(symConfig.fitnessObject)->
                             outputResults(pop.getBest(), "results.txt");

   cout << "Finished" << endl;
   
#ifdef MPI_ENABLED	// Close off MPI systems
    for (int i = 1; i<processSize;i++)
    {
		char message[10000] = "-1 end of file";
		MPI_Send(&message, 10000, MPI_CHAR,i, 1, MPI_COMM_WORLD);
    }		
	MPI_Finalize();
#endif
   
   
   symConfig.cleanUpObjects();

   return 0;
}
