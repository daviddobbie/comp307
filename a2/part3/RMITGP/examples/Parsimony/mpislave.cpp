using namespace std;

#include "Fitness.h"
#include "SymbolicFitness.h"

#include "GeneticProgram.h"

#include "ReturnInt.h"

#include "NodeSet.h"

#include "GPConfig.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>

#include "mpi.h"
#include "GPmpi.h"

void mpislave(int myMPIid, int numberOfNodes, int popSize, GPConfig *config)
{
   //This should be the fitness object for your problem
   config->fitnessObject = new SymbolicFitness(config);

   config->fitnessObject->initFitness();

   int i;
   int mpiNode;
   int numberOfIndividuals=0;
   const int maxNumberOfIndividuals = (popSize / (numberOfNodes - 1));

   GeneticProgram **pop;

   pop = new GeneticProgram* [maxNumberOfIndividuals];
   for(i=0; i<maxNumberOfIndividuals; i++)
   {
      pop[i] = new GeneticProgram(config);
   }

   for(;;) 
   {
      numberOfIndividuals = 
              getIndividuals(maxNumberOfIndividuals, pop, &mpiNode); 

      if (numberOfIndividuals == GPMPI_ERROR)
      {
         cerr << "mpislave error, some sort of problem has occured while "
              << endl 
              << "trying to retreive individuals from the master node " 
              << endl;        
         break; 
      }
      else if (numberOfIndividuals == 0)
         break;

      config->fitnessObject->assignFitness(pop, numberOfIndividuals);

      sendFitnesses(numberOfIndividuals, pop, mpiNode);
   }

   for(i=0; i<maxNumberOfIndividuals; i++)
   {
      delete pop[i];
   }

   delete [] pop;
   config->cleanUpObjects();

   MPI_Finalize();
   exit(0);
}
