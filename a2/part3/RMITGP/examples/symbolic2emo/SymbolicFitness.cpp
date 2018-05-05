/******************************************************************************
 Definition file
 Class:        SymbolicFitness
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <float.h> //for DBL_MAX
#include <cmath>

#include <iostream>
#include <fstream>

#include "SymbolicFitness.h"
#include "ReturnDouble.h"

#include "XDouble.h"

const int SymbolicFitness::FITNESS_CASES = 50;
const int SymbolicFitness::NUM_TEST_CASES = 1000;

SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{
   xValues = new double[FITNESS_CASES];
   targetFunc = new double[FITNESS_CASES];
   generationCounter = 0;
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
      xValues[i] = (config->randomNumGenerator->randReal() * 200) - 100;
      // 1.5X^3 + 3.2X^2 + 4.0X - 127.2
      targetFunc[i] = (1.5 * (xValues[i] * xValues[i] * xValues[i])) +
                      (3.2 * (xValues[i] * xValues[i])) +
                      (4.0 * xValues[i]) -127.2;
   }
   

}

void SymbolicFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i,j;
   ReturnDouble rd;

   for(i=0; i<popSize; i++)
   {
      pop[i]->setObjectiveValue(0, 0.0);
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
            //pop[i]->setFitness(this->worst());
            pop[i]->setObjectiveValue(0, this->worst());
            continue;         
         }
         else
         {
            pop[i]->setObjectiveValue(0, pop[i]->getObjectiveValue(0) + 
                               fabs(targetFunc[j] - rd.getData()));
         }

      }

     pop[i]->setObjectiveValue(1, pop[i]->getSize());
     //pop[i]->setObjectiveValue(1, pop[i]->getDepth());
   }
   
   printf("Generation: %d\n", generationCounter++);
}

void SymbolicFitness::outputResults(GeneticProgram *program, const char *filename)
{
   int i;
   double xDouble;
   ofstream outputFile;
   string progString;
   ReturnDouble rd;

   outputFile.open(filename); 
   if (outputFile.bad())
   {
      cerr << "SymbolicFitness::outputResults Could not open output file"
           << endl;  
      return;
   }

   program->print(progString);

   outputFile << "#Results for evolved program" << endl  
              << "#Output" << endl 
              << "#X    Expected     Actual" << endl;

   for (i=0; i<NUM_TEST_CASES; i++)
   {
      xDouble = (double)i;
      XDouble::setValue(xDouble);

      program->evaluate(&rd);
      
      outputFile << xDouble << " "
   //            << (3 * xDouble) + 14.45 << " "
                 << (1.5 * (xDouble * xDouble * xDouble)) +
                    (3.2 * (xDouble * xDouble)) +
                    (4.0 * xDouble) -127.2 << " "
                 << rd.getData() << endl;
   }

   outputFile.close();
}

bool SymbolicFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.001)
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
