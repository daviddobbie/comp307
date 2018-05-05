/******************************************************************************
 Definition file
 Class:        SymbolicFitness
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <float.h> //for DBL_MAX

#include "SymbolicFitness.h"
#include "ReturnInt.h"
#include "XInt.h"

#include "GPConfig.h"

const int SymbolicFitness::FITNESS_CASES = 50;

SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{
   xValues = new int [FITNESS_CASES];
   targetFunc = new int [FITNESS_CASES];
}

SymbolicFitness::~SymbolicFitness()
{
   delete [] xValues;
   delete [] targetFunc;
}

void SymbolicFitness::initFitness()
{
   int i;
   for(i=0; i<FITNESS_CASES; i++)
   {
      xValues[i] = config->randomNumGenerator->randNum() % 200;
      //targetFunc[i] = xValues[i] + xValues[i] + xValues[i] + 14;
      targetFunc[i] = (3 * (xValues[i] * xValues[i]) / (xValues[i] + 2))
                      + (4 * xValues[i]) -127;
   }
}

void SymbolicFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i,j;
   ReturnInt ri;


   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      for(j=0; j<FITNESS_CASES; j++)
      {
         XInt::setValue(xValues[j]);
         pop[i]->evaluate(&ri);
         pop[i]->setFitness(pop[i]->getFitness() + 
                            abs(targetFunc[j] - ri.getData()));
      }
   }
}

bool SymbolicFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.000001)
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
