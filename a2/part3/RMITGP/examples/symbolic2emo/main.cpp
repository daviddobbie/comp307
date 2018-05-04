using namespace std;

#include "EMOPopulation.h"

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

int main (int argc, char* argv[])
{
   GPConfig symConfig;
   symConfig.numObjectives = 2;
   
   //Declare a population, giving the size and a log file name
   EMOPopulation pop(100, 1000, "run-log.txt", &symConfig);
   string s1;
  
   //Set the rates of mutation etc 
   //pop.setMutationRate(0.28);
   pop.setMutationProbability(0.28);
   //pop.setCrossoverRate(0.70);
   //pop.setElitismRate(0.02);

   //Set the return type for our programs
   pop.setReturnType(ReturnDouble::TYPENUM);

   //Set the depth limit for the system
   symConfig.maxDepth = 6;
   symConfig.minDepth = 3;

   //Set the depth limit for the population
   pop.setDepthLimit(symConfig.maxDepth);
   pop.setMinDepth(symConfig.minDepth);

   //Write out the population every N generations
   //pop.setLogFrequency(100);
   pop.setLogFrequency(1);

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
  
   if (argc == 2)
   { 
      //If there is one command line argument assume its a pop
      //file name
      //Reading a population from a file
      try
      {
         pop.readFromFile(argv[1]);
      }
      catch(string err)
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
      if (pop.evolve(100))
      {
         cout << "Found solution" << endl;
      }
      else
      {
         cout << "Didn't find solution" << endl;
      }

      //pop.getBest()->print(str1);
      //cout << "Best program" << endl
           //<< "Fitness " << pop.getBest()->getFitness() << endl
           //<< str1 << endl;
   }
   catch (string s)
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

   symConfig.cleanUpObjects();

   return 0;
}
