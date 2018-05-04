/******************************************************************************
 Definition file
 Class:        MaxFitness
 Date created: 19/11/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <float.h> //for DBL_MAX
#include <math.h>

#include <iostream>
#include <fstream>

#include "MaxFitness.h"
#include "ReturnDouble.h"

MaxFitness::MaxFitness(GPConfig *conf) : Fitness(conf)
{
	   if(TARPEIAN) conf->activateTarpeian(this); // QCS 20121012
	   if(DDL) {
	   	   conf->activateDDL(this); // QCS 20121012
	   	   conf->ddl->setHeavy(true); // QCS 20121012
	   	   conf->ddl->setVeryHeavy(true); // QCS 20121012
	   }
}

MaxFitness::~MaxFitness() 
{
}

void MaxFitness::initFitness()
{
   goalValue = (double)pow(4.0, pow(2.0, config->maxDepth - 4.0));
   cout << "Goal Value is " << goalValue << endl;
}

void MaxFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i;
   ReturnDouble rd;

   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      pop[i]->evaluate(&rd);

      pop[i]->setFitness(goalValue - rd.getData());
   }
}

bool MaxFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.0001)
         return true;
   }
   return false;
}

bool MaxFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool MaxFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}

bool MaxFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double MaxFitness::best()
{
   return 0.0;
}

double MaxFitness::worst()
{
   return DBL_MAX;
}
