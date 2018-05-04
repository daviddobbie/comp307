#ifndef _MAXFITNESS_H_
#define _MAXFITNESS_H_

/******************************************************************************
 Header file
 Class:        MaxFitness 
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 A fitness class for the MAX problem (Gathercole & Ross).
******************************************************************************/

#include "GeneticProgram.h"
#include "Fitness.h"
#include "GPConfig.h"

#define TARPEIAN true // QCS 20121015
#define DDL true //  QCS 20121015

class MaxFitness : public Fitness
{
   private:
      double goalValue;

   protected:

   public:
      MaxFitness(GPConfig *conf);
      virtual ~MaxFitness();
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
