using namespace std;

#include "Population.h"

#include "Fitness.h"

#include "GeneticProgram.h"

#include "NodeSet.h"
#include "ProgramGenerator.h"

#include "PlusDouble.h"
#include "MultDouble.h"

#include "PointFive.h"

#include "ReturnDouble.h"

#include "MaxFitness.h"

#include "GPConfig.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

int main (int argc, char* argv[])
{
   GPConfig maxConfig;

   //Declare a population, giving the size and a log file name
   Population pop(100, 1000, "maxlog.txt", &maxConfig);
   pop.setNumGenerationBeforeDecimation(3);
   string s1;
  
   //Set the rates of mutation etc 
   pop.setMutationRate(0.10);
   pop.setCrossoverRate(0.89);
   pop.setElitismRate(0.01);

   //Set the return type for our programs
   pop.setReturnType(ReturnDouble::TYPENUM);

   //Set the depth limit for the system
   maxConfig.maxDepth = 6;
   maxConfig.minDepth = 1;

   //Set the depth limit for the population
   pop.setDepthLimit(maxConfig.maxDepth);
   pop.setMinDepth(maxConfig.minDepth);

   //Write out the population every N generations
   pop.setLogFrequency(100);

#ifdef UNIX
   pop.compressGenerationFiles(true);
#endif

   //Do the default initialisation of the configuration
   maxConfig.defaultInit();

   //Add the terminals we need 
   maxConfig.termSet.addNodeToSet(ReturnDouble::TYPENUM, PointFive::generate);

   //Add the functions we need
   maxConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, PlusDouble::generate);
   maxConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, MultDouble::generate);

   //Create the program generator
   maxConfig.programGenerator = new ProgramGenerator(&maxConfig);

   //Set the fitness class to be used
   maxConfig.fitnessObject = new MaxFitness(&maxConfig);

   //Initialise the fitness 
   maxConfig.fitnessObject->initFitness();
  
   if (argc == 2)
   { 
      //If there is one command line argument assume its a pop
      //file name
      //Reading a population from a file
      pop.readFromFile(argv[1]);
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
      if (pop.evolve(200))
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
   catch (string s)
   {
      cerr << s <<endl;
   }


   cout << "Finished" << endl;

   maxConfig.cleanUpObjects();

   return 0;
}
