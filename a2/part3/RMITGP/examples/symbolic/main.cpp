using namespace std;

#include "Population.h"

#include "Fitness.h"
#include "SymbolicFitness.h"
#include "ParallelFitness.h"
#include "TournamentSelection.h"

#include "GeneticProgram.h"

#include "ReturnInt.h"

#include "RandInt.h"
#include "XInt.h"

#include "PlusInt.h"
#include "MinusInt.h"
#include "MultInt.h"
#include "DivideInt.h"

#include "NodeSet.h"

#include "ProgramGenerator.h"

#include "GPConfig.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

#ifdef USEMPI
   #include "mpi.h"
   #include "mpislave.h"
#endif

int main (int argc, char* argv[])
{
   GPConfig symConfig;

   //Declare a population, giving the size and a log file name
   Population pop(100, 1000, "run-log.txt", &symConfig);
   string s1;
  
   //Set the rates of mutation etc 
   pop.setMutationRate(0.28);
   pop.setCrossoverRate(0.70);
   pop.setElitismRate(0.02);

   //Alternative way to set mutation crossover etc
   //pop.setNumForMutation(10);
   //pop.setNumForCrossover(180);
   //pop.setNumForElitism(10);

   //Do the default initialisation of the 
   //GPConfig class
   symConfig.defaultInit();

   delete symConfig.selectionOperator;
   //Set the selection operator to be tournament selection
   symConfig.selectionOperator = new TournamentSelection(5);

   //Add the terminals we need 
   symConfig.termSet.addNodeToSet(ReturnInt::TYPENUM, RandInt::generate);
   symConfig.termSet.addNodeToSet(ReturnInt::TYPENUM, XInt::generate);

   //Add the functions we need
   symConfig.funcSet.addNodeToSet(ReturnInt::TYPENUM, PlusInt::generate);
   symConfig.funcSet.addNodeToSet(ReturnInt::TYPENUM, MinusInt::generate);
   symConfig.funcSet.addNodeToSet(ReturnInt::TYPENUM, MultInt::generate);
   symConfig.funcSet.addNodeToSet(ReturnInt::TYPENUM, DivideInt::generate);

   //Set the return type for our programs
   pop.setReturnType(ReturnInt::TYPENUM);

   //Set the depth limit for the system
   symConfig.maxDepth = 7;

   //Set the depth limit for the population
   pop.setDepthLimit(symConfig.maxDepth);
   pop.setMinDepth(1);

   symConfig.programGenerator = new ProgramGenerator(&symConfig);

   //Set the fitness class to be used
   #ifdef USEMPI
      int mpiID;
      int mpiNumNodes;
      MPI_Init(&argc, &argv);
      MPI_Comm_rank(MPI_COMM_WORLD, &mpiID);
      MPI_Comm_size(MPI_COMM_WORLD, &mpiNumNodes);

      //If this process is a slave run the slave code
      if (mpiID != 0)
      {
         mpislave(mpiID, mpiNumNodes, pop.getNumIndividuals(), &symConfig);
         return 0;
      }

      symConfig.fitnessObject = new ParallelFitness(&symConfig);
   #else
      symConfig.fitnessObject = new SymbolicFitness(&symConfig);
   #endif

   //Initialise the fitness 
   symConfig.fitnessObject->initFitness();

   #if 1
      pop.generateInitialPopulation();
   #else
      //Reading a population from a file
      pop.readFromFile(argv[1]);
   #endif

   //Write out the population every 20 generations
   pop.setLogFrequency(20);

#ifdef UNIX
   pop.compressGenerationFiles(true);
#endif

   try
   {
      string str1;
   
      /*Do 1000 generations, returns true if solution is found
        (see fitness class*/
      if (pop.evolve(500))
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
   catch (string &s)
   {
      cerr << s <<endl;
   }

   cout << "Finished" << endl;


   #ifdef USEMPI
      dynamic_cast<ParallelFitness *>(symConfig.fitnessObject)
                                                           ->shutDownSlaves();
      MPI_Finalize();
   #endif

   symConfig.cleanUpObjects(); 
   return 0;
}
