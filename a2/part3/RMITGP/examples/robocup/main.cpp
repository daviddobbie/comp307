using namespace std;

#include "Population.h"

#include "Fitness.h"

#include "GeneticProgram.h"

#include "NodeSet.h"
#include "ProgramGenerator.h"

//Functions
#include "Dash.h"
#include "Turn.h"
#include "Kick.h"
#include "ExecTwo.h"

//Terminals
#include "Power.h"
#include "Angle.h"

//Return types
#include "ReturnAction.h"
#include "ReturnPower.h"
#include "ReturnAngle.h"

//Fitness
#include "RobocupFitness.h"

#include "GPConfig.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

int main (int argc, char* argv[])
{
   GPConfig roboConfig;

   //Declare a population, giving the size and a log file name
   Population pop(20, "runlog.txt", &roboConfig);
   string s1;
  
   //Set the rates of mutation etc 
   pop.setMutationRate(0.28);
   pop.setCrossoverRate(0.70);
   pop.setElitismRate(0.02);

   //Do the default initialisation of the 
   //GPConfig class
   roboConfig.defaultInit();

   //Add the terminals we need 
   roboConfig.termSet.addNodeToSet(ReturnPower::TYPENUM, Power::generate);
   roboConfig.termSet.addNodeToSet(ReturnAngle::TYPENUM, GPAngle::generate);

   //Add the functions we need
   roboConfig.funcSet.addNodeToSet(ReturnAction::TYPENUM, Dash::generate);
   roboConfig.funcSet.addNodeToSet(ReturnAction::TYPENUM, Turn::generate);
   roboConfig.funcSet.addNodeToSet(ReturnAction::TYPENUM, Kick::generate);
   roboConfig.funcSet.addNodeToSet(ReturnAction::TYPENUM, ExecTwo::generate);

   //Set the return type for our programs
   pop.setReturnType(ReturnAction::TYPENUM);

   //Set the depth limit for the system
   roboConfig.maxDepth = 3;
   roboConfig.minDepth = 1;

   //Set the depth limit for the population
   pop.setDepthLimit(roboConfig.maxDepth);
   pop.setMinDepth(roboConfig.minDepth);

   roboConfig.programGenerator = new ProgramGenerator(&roboConfig);

   //Set the fitness class to be used
   roboConfig.fitnessObject = new RobocupFitness(&roboConfig);

   //Initialise the fitness 
   roboConfig.fitnessObject->initFitness();

   #if 1
      pop.generateInitialPopulation();
   #else
      //Reading a population from a file
      pop.readFromFile(argv[1]);
   #endif

   //Write out the population every 5 generations
   pop.setLogFrequency(10);

#ifdef UNIX
   pop.compressGenerationFiles(true);
#endif

   try
   {
      string str1;
   
      /*Do 100 generations, returns true if solution is found
        (see fitness class)*/
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
   catch (string s)
   {
      cerr << s <<endl;
   }

   cout << "Finished" << endl;

   roboConfig.cleanUpObjects();

   return 0;
}
