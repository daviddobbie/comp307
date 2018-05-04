#ifndef _SYMBOLICFITNESS_H_
#define _SYMBOLICFITNESS_H_

/******************************************************************************
 Header file
 Class:        SymbolicFitness 
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 A symbolic regression fitness class
******************************************************************************/

#include "GeneticProgram.h"
#include "Fitness.h"
#include "GPConfig.h"

#define TARPEIAN true // QCS 20120917
#define DDL true //  QCS 20120930

class SymbolicFitness : public Fitness
{
   private:
      //This constant controls the number of points to use for
      //training the programs
      static const int FITNESS_CASES;

      double *xValues;
      double *targetFunc;

      //This constant controls the number of points to use for
      //writing the test data out (x rang 0 (NUM_TEST_CASES-1))
      static const int NUM_TEST_CASES;
      
      int generationCounter; // Used only to print out the progress

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

      /******************************************
       Writes out the results of executing a 
       program to the file. Along with the 
       desired results. 
      *******************************************/
      void outputResults(GeneticProgram *program, const char *filename);
};

#endif
