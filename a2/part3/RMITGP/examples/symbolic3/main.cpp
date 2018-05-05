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
#include "If.h"
#include "LessThan.h"
#include "GreaterThan.h"

#include "XDouble.h"
#include "RandDouble.h"

#include "ReturnDouble.h"
#include "ReturnBoolean.h"

#include "SymbolicFitness.h"

#include "GPConfig.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

int main (int argc, char* argv[])
{
   GPConfig symConfig;

   //Declare a population, giving the size and a log file name
   Population pop(1000, "run-log.txt", &symConfig);
   string s1;
  
   //Set the rates of mutation etc 
   pop.setMutationRate(0.28);
   pop.setCrossoverRate(0.70);
   pop.setElitismRate(0.02);

   //Do the default initialisation of the 
   //GPConfig class
   symConfig.defaultInit();

   //Add the terminals we need 
   symConfig.termSet.addNodeToSet(ReturnDouble::TYPENUM, RandDouble::generate);
   symConfig.termSet.addNodeToSet(ReturnDouble::TYPENUM, XDouble::generate);

   //Add the functions we need
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, PlusDouble::generate);
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, MinusDouble::generate);
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, MultDouble::generate);
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, DivideDouble::generate);
   symConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, If::generate);
   symConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, LessThan::generate);
   symConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, GreaterThan::generate);

   //Set the return type for our programs
   pop.setReturnType(ReturnDouble::TYPENUM);

   //Set the depth limit for the system
   symConfig.maxDepth = 6;
   symConfig.minDepth = 1;

   //Set the depth limit for the population
   pop.setDepthLimit(symConfig.maxDepth);
   pop.setMinDepth(symConfig.minDepth);

   symConfig.programGenerator = new ProgramGenerator(&symConfig);

   //Set the fitness class to be used
   symConfig.fitnessObject = new SymbolicFitness(&symConfig);

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
      if (pop.evolve(100))
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

   symConfig.cleanUpObjects();

   return 0;
}
