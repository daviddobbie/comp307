#ifndef _PARALLELFITNESS_H_
#define _PARALLELFITNESS_H_

/******************************************************************************
 Header file
 Class:        ParallelFitness 
 Date created: 15/07/2002
 Written by:   Dylan Mawhinney

 A fitness class which uses mpi to do parallel fitness evaluations 
******************************************************************************/

class GPConfig;

#include "GeneticProgram.h"
#include "Fitness.h"

class ParallelFitness : public Fitness
{
   private:
      int mpiID;       //The mpi id of this task (process)
      int numMPITasks; //The total number of mpi tasks

   protected:

   public:
      ParallelFitness(GPConfig *conf);

      virtual void initFitness();
      virtual void assignFitness(GeneticProgram* pop[], int popSize);
      virtual bool solutionFound(GeneticProgram* pop[], int popSize);
      virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

      virtual double best();
      virtual double worst();

      virtual void shutDownSlaves();
};

#endif
