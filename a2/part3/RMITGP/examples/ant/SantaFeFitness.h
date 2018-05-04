#ifndef _SANTAFEFITNESS_H_
#define _SANTAFEFITNESS_H_

/******************************************************************************
 Header file
 Class:        SantaFeFitness 
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 The Santa Fe Ant trail fitness class.
******************************************************************************/

#include "GeneticProgram.h"
#include "Fitness.h"

#define TARPEIAN true // QCS 20121012
#define DDL true //  QCS 20121012

class SantaFeFitness : public Fitness
{
   private:
      static const int MAP_WIDTH;
      static const int MAP_HEIGHT;
      static const int MAX_STEPS;

      static const int NORTH;
      static const int EAST;
      static const int SOUTH;
      static const int WEST;

      int **map;
      int direction;
      int foodLeft;
      int x;
      int y;
      int simStep;

   protected:

   public:
      SantaFeFitness(GPConfig *conf);
      virtual ~SantaFeFitness();

      virtual void initFitness();
      virtual void assignFitness(GeneticProgram* pop[], int popSize);
      virtual bool solutionFound(GeneticProgram* pop[], int popSize);
      virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

      virtual double best();
      virtual double worst();

      void eat();
      void move();
      void turnLeft();
      void turnRight();      
      bool ifFoodAhead();
};

#endif
