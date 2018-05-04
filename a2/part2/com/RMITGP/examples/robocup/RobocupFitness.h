#ifndef _ROBOCUPFITNESS_H_
#define _ROBOCUPFITNESS_H_

/******************************************************************************
 Header file
 Class:        RobocupFitness 
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 A fitness class for the robocup problem.
******************************************************************************/

class GPConfig;

#include <pthread.h>

#include "GeneticProgram.h"
#include "Fitness.h"

//Robocup include
#include "player.h"

class RobocupFitness : public Fitness
{
   private:
      pthread_t serverID;
      Player *players;

   protected:

   public:
      RobocupFitness(GPConfig *conf);

      virtual void initFitness();
      virtual void assignFitness(GeneticProgram* pop[], int popSize);
      virtual bool solutionFound(GeneticProgram* pop[], int popSize);
      virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

      virtual double best();
      virtual double worst();

      void startServer();
};

#endif
