#ifndef _PREDATORPREYFITNESS_H_
#define _PREDATORPREYFITNESS_H_

/******************************************************************************
 Header file
 Class:        PredatorPreyFitness 
 Date created: 19/09/2002
 Written by:   Dylan Mawhinney

 The fitness class for the predator prey problem.
******************************************************************************/

class GPConfig;

#include "GeneticProgram.h"
#include "CoEvolutionFitness.h"

#include "ReturnMove.h"

class PredatorPreyFitness : public CoEvolutionFitness
{
   private:
      static const int GRID_WIDTH;
      static const int GRID_HEIGHT;
      static const int MAX_STEPS;
      static const int NUM_TESTS;

      bool predators;
 
      class Pos
      {
         public:
            int x;
            int y;
      };

      Pos predPosition;
      Pos preyPosition;

      int caught;
      int simulationStep;

      bool showGame;

      bool doActions(ReturnMove& rm1, ReturnMove& rm2);
      void printBoard();
   protected:

   public:
      PredatorPreyFitness(GPConfig *conf, bool pred);
      virtual void initFitness();

      virtual void resetGrid();

      virtual void assignFitness(GeneticProgram* pop[], int popSize);
      virtual void assignFitness(GeneticProgram **pop1, GeneticProgram **pop2,
                                 int numIndividuals1, int numIndividuals2);

      virtual bool solutionFound(GeneticProgram* pop[], int popSize);
      virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

      virtual double best();
      virtual double worst();

      /**********************************************************
       Call this method if you want to watch the games
      **********************************************************/
      void turnOnDisplay();

       /******************************************************
        These methods allow the functions and terminals to
        get information about the predator and prey on the
        grid.
       *******************************************************/
      int getPredX() const; 
      int getPredY() const;
      int getPreyX() const;
      int getPreyY() const;
};

#endif
