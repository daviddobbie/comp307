#include <iostream>

using namespace std;

#include "Population.h"
#include "ProgramGenerator.h"
#include "NodeSet.h"

#include "Move.h"
#include "TurnLeft.h"
#include "TurnRight.h"

#include "Prog2.h"
#include "Prog3.h"
#include "IfFoodAhead.h"

#include "ReturnDummy.h"

#include "SantaFeFitness.h"

#include "GPConfig.h"

int main(int argc, char *argv[])
{
   GPConfig antConfig;

   //Declare our population of ant programs
   Population antPop(1000, 10000, "antlog.txt", &antConfig);

   antPop.setMutationRate(0.28);
   antPop.setCrossoverRate(0.70);
   antPop.setElitismRate(0.02);
   //antPop.setNumGenerationBeforeDecimation(3);

   antPop.setReturnType(ReturnDummy::TYPENUM);

   #ifdef UNIX
   antPop.compressGenerationFiles(true);
   #endif

   antPop.setLogFrequency(50);

   antConfig.defaultInit(); 

   //Add the terminals
   antConfig.termSet.addNodeToSet(ReturnDummy::TYPENUM, Move::generate); 
   antConfig.termSet.addNodeToSet(ReturnDummy::TYPENUM, TurnLeft::generate); 
   antConfig.termSet.addNodeToSet(ReturnDummy::TYPENUM, TurnRight::generate); 

   //Add the functions
   antConfig.funcSet.addNodeToSet(ReturnDummy::TYPENUM, Prog2::generate); 
   antConfig.funcSet.addNodeToSet(ReturnDummy::TYPENUM, Prog3::generate); 
   antConfig.funcSet.addNodeToSet(ReturnDummy::TYPENUM, IfFoodAhead::generate); 


   antConfig.maxDepth = 5;
   antConfig.minDepth = 1;
   antPop.setDepthLimit(antConfig.maxDepth);
   antPop.setMinDepth(antConfig.minDepth);
  
   antConfig.programGenerator = new ProgramGenerator(&antConfig); 
   antConfig.fitnessObject = new SantaFeFitness(&antConfig);
   antConfig.fitnessObject->initFitness();

   antPop.generateInitialPopulation();

   try
   {
      string str1;
  
      /*Do 100 generations, returns true if solution is found
        (see fitness class*/
      if (antPop.evolve(200))
      {
         cout << "Found solution" << endl;
      }
      else
      {
         cout << "Didn't find solution" << endl;
      }

      antPop.getBest()->print(str1);
      cout << "Best program" << endl
           << "Fitness " << antPop.getBest()->getFitness() << endl
           << str1 << endl;
   }
   catch(string &s)
   {
      cerr << "Error caught" << endl << s << endl;
   }

   antConfig.cleanUpObjects();

   return 0;
}
