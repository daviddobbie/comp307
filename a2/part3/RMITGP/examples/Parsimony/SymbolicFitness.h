#ifndef _SYMBOLICFITNESS_H_
#define _SYMBOLICFITNESS_H_

/******************************************************************************
 Header file
 Class:        SymbolicFitness 
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 A symbolic regression fitness class
******************************************************************************/

class GPConfig;

#include "GeneticProgram.h"
#include "Fitness.h"

class SymbolicFitness : public Fitness
{
   private:
      static const int FITNESS_CASES;

      int *xValues;
      int *targetFunc;

   protected:

   public:
      SymbolicFitness(GPConfig *conf);
      virtual ~SymbolicFitness();
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
