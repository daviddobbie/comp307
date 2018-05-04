using namespace std;

#include <cstdlib>

#include "CoEvolutionPopulation.h"
#include "PredatorPreyFitness.h"

#include "GeneticProgram.h"

#include "NodeSet.h"
#include "ProgramGenerator.h"

#include "If.h"
#include "LessThan.h"
#include "GreaterThan.h"
#include "And.h"
#include "Or.h"

#include "GetPredX.h"
#include "GetPredY.h"
#include "GetPreyX.h"
#include "GetPreyY.h"

#include "MoveUp.h"
#include "MoveDown.h"
#include "MoveLeft.h"
#include "MoveRight.h"

#include "ReturnMove.h"
#include "ReturnCoord.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

int main (int argc, char* argv[])
{
   //We need two config objects because we have 2 populations
   GPConfig predConfig;
   GPConfig preyConfig;

   //Declare a population, giving the size and a log file name
   CoEvolutionPopulation predPop(200, "pred-log.txt", &predConfig, "pred");
   CoEvolutionPopulation preyPop(200, "prey-log.txt", &preyConfig, "prey");

   string s1;
  
   //Set the rates of mutation etc 
   predPop.setMutationRate(0.28);
   predPop.setCrossoverRate(0.70);
   predPop.setElitismRate(0.02);

   preyPop.setMutationRate(0.28);
   preyPop.setCrossoverRate(0.70);
   preyPop.setElitismRate(0.02);

   //Do the default initialisation of the 
   //GPConfig class
   predConfig.defaultInit();
   preyConfig.defaultInit();

   //Add the terminals we need to the predator config 
   predConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveUp::generate);
   predConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveDown::generate);
   predConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveLeft::generate);
   predConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveRight::generate);

   predConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPredX::generate);
   predConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPredY::generate);
   predConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPreyX::generate);
   predConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPreyY::generate);

   predConfig.funcSet.addNodeToSet(ReturnMove::TYPENUM, If::generate);
   predConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, LessThan::generate);
   predConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, GreaterThan::generate);
   predConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, And::generate);
   predConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, Or::generate);

   //Add the terminals we need to the prey config 
   preyConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveUp::generate);
   preyConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveDown::generate);
   preyConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveLeft::generate);
   preyConfig.termSet.addNodeToSet(ReturnMove::TYPENUM, MoveRight::generate);

   preyConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPredX::generate);
   preyConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPredY::generate);
   preyConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPreyX::generate);
   preyConfig.termSet.addNodeToSet(ReturnCoord::TYPENUM, GetPreyY::generate);

   preyConfig.funcSet.addNodeToSet(ReturnMove::TYPENUM, If::generate);
   preyConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, LessThan::generate);
   preyConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, GreaterThan::generate
);
   preyConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, And::generate);
   preyConfig.funcSet.addNodeToSet(ReturnBoolean::TYPENUM, Or::generate);


   //Set the return type for our programs
   predPop.setReturnType(ReturnMove::TYPENUM);
   preyPop.setReturnType(ReturnMove::TYPENUM);

   //Set the depth limit for the system
   predConfig.maxDepth = 6;
   predConfig.minDepth = 1;

   preyConfig.maxDepth = 6;
   preyConfig.minDepth = 1;

   //Set the depth limit for the population
   predPop.setDepthLimit(predConfig.maxDepth);
   predPop.setMinDepth(predConfig.minDepth);

   preyPop.setDepthLimit(preyConfig.maxDepth);
   preyPop.setMinDepth(preyConfig.minDepth);

   //Construct the program generators
   predConfig.programGenerator = new ProgramGenerator(&predConfig);
   preyConfig.programGenerator = new ProgramGenerator(&preyConfig);

   //Set the fitness class to be used
   predConfig.fitnessObject = new PredatorPreyFitness(&predConfig, true);
   preyConfig.fitnessObject = new PredatorPreyFitness(&preyConfig, false);


   //Initialise the fitness 
   predConfig.fitnessObject->initFitness();
   preyConfig.fitnessObject->initFitness();


   if (argc == 1)
   {
      //Generate the initial population
      predPop.generateInitialPopulation();
      preyPop.generateInitialPopulation();
   }
   else if (argc == 3)
   {
      try
      {
         cout << "Viewing population" << endl;
         predPop.readFromFile(argv[1]);
         preyPop.readFromFile(argv[2]);
         dynamic_cast<PredatorPreyFitness *>(predConfig.fitnessObject)
                                                        ->turnOnDisplay();
         predPop.setOtherPopulation(&preyPop);
         preyPop.setOtherPopulation(&predPop);
         predPop.evolve(1);
      }
      catch (string err)
      {
         cerr << err << endl;
         predConfig.cleanUpObjects();
         preyConfig.cleanUpObjects();
         exit(EXIT_FAILURE);
      }
      return EXIT_SUCCESS;
   }
   else
   {
      cerr << "Usage: " << argv[0] << " [predpopulation preypopulation]" 
           << endl; 
      predConfig.cleanUpObjects();
      preyConfig.cleanUpObjects();
      return EXIT_FAILURE;
   } 
 

   //Write out the population every 20 generations
   predPop.setLogFrequency(400);
   preyPop.setLogFrequency(400);

#ifdef UNIX
   predPop.compressGenerationFiles(true);
   preyPop.compressGenerationFiles(true);
#endif

   predPop.setOtherPopulation(&preyPop);
   preyPop.setOtherPopulation(&predPop);

   try
   {
      string str1;
      int j;
 
      /*Do 100 generations doing 1 at a time for each*/
      /* 
      for (j=0; j<100; j++) 
      {
         predPop.evolve(1);
         preyPop.evolve(1);
      }
      */

      /*Do 100 more, but stepping 10 at a time*/
      for (j=0; j<5; j++)
      {
         predPop.evolve(400);
         preyPop.evolve(400);
      }


      str1 = "";
      predPop.getBest()->print(str1);
      cout << "Best predator program" << endl
           << "Fitness " << predPop.getBest()->getFitness() << endl
           << str1 << endl;

      str1 = "";
      preyPop.getBest()->print(str1);
      cout << "Best prey program" << endl
           << "Fitness " << preyPop.getBest()->getFitness() << endl
           << str1 << endl;
   }
   catch (string s)
   {
      cerr << s <<endl;
   }

   cout << "Finished" << endl;

   predConfig.cleanUpObjects();
   preyConfig.cleanUpObjects();

   return EXIT_SUCCESS;
}
