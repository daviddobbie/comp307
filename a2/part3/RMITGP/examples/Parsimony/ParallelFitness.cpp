/******************************************************************************
 Definition file
 Class:        ParallelFitness 
 Date created: 15/07/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

//FIX: REMOVE
#include <iostream>
#include <fstream>

#include <float.h>

#include "ParallelFitness.h"

#include "mpi.h"
#include "GPmpi.h"

#include "GPConfig.h"

ParallelFitness::ParallelFitness(GPConfig *conf) : Fitness(conf),
                                                   mpiID(-1), numMPITasks(0)
{
}
                                    
void ParallelFitness::initFitness()
{
   MPI_Comm_rank(MPI_COMM_WORLD, &mpiID);
   MPI_Comm_size(MPI_COMM_WORLD, &numMPITasks);
}

void ParallelFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i;

   //Set each programs fitness to 0 and the program id 
   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      pop[i]->setProgramID(i);
   }

   int indivPerTask = popSize / (numMPITasks - 1);
   int extraIndiv = popSize % (numMPITasks - 1);

   int taskID;

   for (i=0, taskID=0; i< (popSize - extraIndiv); i+= indivPerTask)
   {
      if (taskID == this->mpiID)
         taskID++;

      sendIndividuals(indivPerTask, pop + i, taskID);
      taskID++;
   } 

   //Do the extra left over individuals 
   if (extraIndiv > 0)
   {
      taskID=0;
      if (taskID == mpiID)
         taskID++;

      sendIndividuals(extraIndiv, pop + i, taskID);
   }

   //Receive from each slave
   for (i=0; i< (popSize - extraIndiv); i+= indivPerTask)
      getFitnesses(indivPerTask, pop);

   //If there are extra individuals left over
   if (extraIndiv > 0)
      getFitnesses(indivPerTask, pop);
}

void ParallelFitness::shutDownSlaves()
{
   int taskID=0;
   int tmp=0;

   while (taskID < numMPITasks)
   {
      if (taskID == mpiID)
         taskID++;

      MPI_Send(&tmp, 1, MPI_INT, taskID, 0, MPI_COMM_WORLD);
      taskID++;
   }
}

bool ParallelFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.000001)
         return false;
   }
   return false;
}

bool ParallelFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool ParallelFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}

bool ParallelFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double ParallelFitness::best()
{
   return 0.0;
}

double ParallelFitness::worst()
{
   return DBL_MAX;
}
