#ifndef _CLASSIFICATIONFITNESS_H_
#define _CLASSIFICATIONFITNESS_H_

/*****************************************************************************
 Header file
 Class:         ClassificationFitness 
 Date created:  29/03/2006
 Written by:    Djaka W Kurniawan
 Date Modified: 18/07/2007 
 Modified by:   Danny Fang
 
 A texture classification fitness class
 Modified version contains functions to facilitate for storing information
 about the number of different resulting cases from the tests such as false
 positives.
 *****************************************************************************/

class GPCconfig;

#include "GeneticProgram.h"
#include "Fitness.h"
#include <string.h>
#include <ctime>
#ifdef MPI_ENABLED
#include "mpi.h"
#endif

extern int POP_SIZE;
extern int INITIAL_POP_SIZE;
extern int MAXDEPTH;
extern int MINDEPTH;
extern int EVOLVE;
extern float MUTATION_RATE;
extern float CROSSOVER_RATE;
extern float ELITISM_RATE;
extern bool TARPEIAN; // QCS 20121012
extern bool DDL;
extern int DYNAMIC_SELECTION;
extern int TRAINING; 
extern int TESTING; 
extern bool EMO;
extern time_t run_time;

class ClassificationFitness : public Fitness
{
private:
    int *rightClassified;
    // Variable for keeping track of false positives and false negatives
    int *truepos;
    int *trueneg;
    int *falseneg;
    int *falsepos;
	
public:
    ClassificationFitness(GPConfig *conf);
    ~ClassificationFitness();
    virtual void initFitness();
    virtual void assignFitness(GeneticProgram* pop[], int popSize);
    virtual bool solutionFound(GeneticProgram* pop[], int popSize);
    virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
    virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
    virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);
    virtual double best();
    virtual double worst();
	
	void dynamicSelection(GeneticProgram* pop, int totpos, int totneg);
	void normalSelection(GeneticProgram* pop, int totpos, int totneg);
    #ifdef MPI_ENABLED
    void slaveProcess(GeneticProgram* pop);
    void masterProcess(GeneticProgram* pop[], int popSize);
    #endif
	
protected:
};

#endif
