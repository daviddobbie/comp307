/******************************************************************************
 Definition file
 Class:        SymbolicFitness
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <float.h> //for DBL_MAX
#include <math.h>

#include "SymbolicFitness.h"
#include "ReturnDouble.h"
#include "XDouble.h"

#include "GPConfig.h"

SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{
}

void SymbolicFitness::initFitness()
{
   int i;
   for(i=0; i<FITNESS_CASES; i++)
   {
      xValues[i] = (config->randomNumGenerator->randReal() * 200) - 100;

      //This target function is a little strange.
      //Basically if the value of the x coordinate is less than 30
      //the target function will be 3x + 14.45 otherwise it will be
      //2x^2 + x
      //This is to properly test the conditional execution
      //available in this example.
      if (xValues[i] < 30.0)
         targetFunc[i] = xValues[i] + xValues[i] + xValues[i] + 14.45;
      else
         targetFunc[i] = (2 * xValues[i] * xValues[i]) + xValues[i];
   }
}

void SymbolicFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i,j;
   ReturnDouble rd;

   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      for(j=0; j<FITNESS_CASES; j++)
      {
         XDouble::setValue(xValues[j]);
         pop[i]->evaluate(&rd);

         //Unfortunately we have to check for NaN
         //We should probably also check for Infinity but I'm not sure
         //of a portable way to do that.
         #ifdef WIN32 
         if (_isnan(rd.getData()))
         #else
         if (isnan(rd.getData()))
         #endif
         {
            pop[i]->setFitness(this->worst());
            continue;         
         }
         else
         {
            pop[i]->setFitness(pop[i]->getFitness() + 
                               fabs(targetFunc[j] - rd.getData()));
         }
      }
   }
}

bool SymbolicFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.0001)
         return true;
   }
   return false;
}

bool SymbolicFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool SymbolicFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}

bool SymbolicFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double SymbolicFitness::best()
{
   return 0.0;
}

double SymbolicFitness::worst()
{
   return DBL_MAX;
}
