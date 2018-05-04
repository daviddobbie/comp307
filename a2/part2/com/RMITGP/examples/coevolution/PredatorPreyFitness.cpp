/******************************************************************************
 Definition file
 Class:        PredatorPreyFitness 
 Date created: 19/09/2002
 Written by:   Dylan Mawhinney

 See header file for details.
******************************************************************************/

#include <float.h>

#include <iostream>

using namespace std;

#include "PredatorPreyFitness.h"
#include "GPConfig.h"
#include "ReturnMove.h"

const int PredatorPreyFitness::GRID_WIDTH = 78;
const int PredatorPreyFitness::GRID_HEIGHT = 20;
const int PredatorPreyFitness::MAX_STEPS = 120;
const int PredatorPreyFitness::NUM_TESTS = 1;

PredatorPreyFitness::PredatorPreyFitness(GPConfig *conf, bool pred) 
                                                 : CoEvolutionFitness(conf),
                                                   predators(pred),
                                                   simulationStep(0),
                                                   showGame(false)
{
}

void PredatorPreyFitness::initFitness()
{
   caught = 0;
   simulationStep = 0; 
   resetGrid();
}

void PredatorPreyFitness::resetGrid()
{
   predPosition.x = config->randomNumGenerator->randNum() % GRID_WIDTH;
   predPosition.y = config->randomNumGenerator->randNum() % GRID_HEIGHT;
   preyPosition.x = config->randomNumGenerator->randNum() % GRID_WIDTH;
   preyPosition.y = config->randomNumGenerator->randNum() % GRID_HEIGHT;
}

void PredatorPreyFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   throw string("PredatorPreyFitness::assignFitness error not supported!");
}

void PredatorPreyFitness::assignFitness(GeneticProgram **pop1,
                                        GeneticProgram **pop2,
                                        int numIndividuals1,
                                        int numIndividuals2)
{
   int i;
   int j;
   ReturnMove rm1, rm2;

   /*Do predators evolution*/
      for(i=0; i<numIndividuals1; i++)   
      {
         initFitness();
         
         for (j=0; j<NUM_TESTS; j++)
         {

            int secondIndividual = 
                       config->selectionOperator->select(pop2,
                                                         numIndividuals2,
                                                         config); 

            while(simulationStep < MAX_STEPS)
            {
               if (showGame)
                  printBoard();

               pop1[i]->evaluate(&rm1);
               pop2[secondIndividual]->evaluate(&rm2);
       
               bool stop;
 
               if (predators) 
                  stop = doActions(rm1, rm2); 
               else
                  stop = doActions(rm2, rm1);
 
               if (stop) 
               {
                  caught++;
                  resetGrid();
               }

               simulationStep++;
            }
            resetGrid();
         }   
    
         if (predators) 
            pop1[i]->setFitness(1.0 / (1.0 + caught));
         else
            pop1[i]->setFitness(0.01 * (caught * caught));
      }
}

bool PredatorPreyFitness::doActions(ReturnMove &rm1, ReturnMove &rm2)
{
   if (rm1.getData() == ReturnMove::UP)
      predPosition.y++; 
   else if (rm1.getData() == ReturnMove::DOWN)
      predPosition.y--; 
   else if (rm1.getData() == ReturnMove::LEFT)
      predPosition.x--; 
   else if (rm1.getData() == ReturnMove::RIGHT)
      predPosition.x++; 

   if (rm2.getData() == ReturnMove::UP)
      preyPosition.y++;
   else if (rm2.getData() == ReturnMove::DOWN)
      preyPosition.y--;
   else if (rm2.getData() == ReturnMove::LEFT)
      preyPosition.x--;
   else if (rm2.getData() == ReturnMove::RIGHT)
      preyPosition.x++;

   //Grid is toroidal players wrap around
   if (predPosition.x < 0)
      predPosition.x = GRID_WIDTH-1;
   else if (predPosition.x > GRID_WIDTH)
      predPosition.x = 0;

   if (preyPosition.x < 0)
      preyPosition.x = GRID_WIDTH - 1;
   else if (preyPosition.x > GRID_WIDTH)
      preyPosition.x = 0; 

   if (predPosition.y < 0)
      predPosition.y = GRID_HEIGHT - 1;
   else if (predPosition.y > GRID_HEIGHT)
      predPosition.y = 0; 

   if (preyPosition.y < 0)
      preyPosition.y = GRID_HEIGHT - 1;
   else if (preyPosition.y > GRID_HEIGHT)
      preyPosition.y = 0;

   if ((predPosition.x == preyPosition.x) && (preyPosition.y == preyPosition.y))
      return true;

   return false;
} 

void PredatorPreyFitness::printBoard()
{
   int i, j;

   cout << "--------------------------------------------------------------------------------"<< endl;

   for (i=GRID_HEIGHT; i>=0; i--)
   {
      cout << "|";
      for (j=0; j<GRID_WIDTH; j++)
      {
         if ((predPosition.x == j) && (predPosition.y == i))
            cout << "0";
         else if ((preyPosition.x == j) && (preyPosition.y == i))
            cout << "1";
         else
            cout << " ";
      }
      cout << "|" << endl;
   }

   cout << "--------------------------------------------------------------------------------"<< endl;

}

bool PredatorPreyFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   return false;
}

bool PredatorPreyFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool PredatorPreyFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}


bool PredatorPreyFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double PredatorPreyFitness::best()
{
   return 0.0;
}

double PredatorPreyFitness::worst()
{
   return DBL_MAX;
}

void PredatorPreyFitness::turnOnDisplay()
{
   showGame = true;
}

int PredatorPreyFitness::getPredX() const 
{
   return predPosition.x;
}

int PredatorPreyFitness::getPredY() const
{
   return predPosition.y;
}

int PredatorPreyFitness::getPreyX() const
{
   return preyPosition.x;
}

int PredatorPreyFitness::getPreyY() const
{
   return preyPosition.y;
}
