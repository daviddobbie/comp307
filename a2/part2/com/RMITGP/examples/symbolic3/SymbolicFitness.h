#ifndef _SYMBOLICFITNESS_H_
#define _SYMBOLICFITNESS_H_

/******************************************************************************
 Header file
 Class:        SymbolicFitness 
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 A symbolic regression fitness class
******************************************************************************/

class GPCconfig;

#include "GeneticProgram.h"
#include "Fitness.h"

#define FITNESS_CASES 50

class SymbolicFitness : public Fitness
{
   private:
      double xValues[FITNESS_CASES];
      double targetFunc[FITNESS_CASES];

   protected:

   public:
      SymbolicFitness(GPConfig *conf);

      virtual void initFitness();
      virtual void assignFitness(GeneticProgram* pop[], int popSize);
      virtual bool solutionFound(GeneticProgram* pop[], int popSize);
      virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

      virtual double best();
      virtual double worst();
      
};

#endif
