#ifndef _GPMPI_H_
#define _GPMPI_H_

/******************************************************************************
 Header file
 Package:      mpi GP utility functions
 Date created: 10/09/2002
 Written by:   Dylan Mawhinney

 This package contains functions for sending and receiving individuals
 between communicating mpi processes. 
***************************************************************************/

#include "GeneticProgram.h"
#include "mpi.h"

#define GPMPI_ERROR -1

//Send programs from the master to the slave nodes
void sendIndividuals(int numToSend, GeneticProgram **programList, int node);

//Receive programs from the master
int getIndividuals(int maxInd, GeneticProgram **programList, int *node);

//Send fitness values from the slave back to the master
void sendFitnesses(int numToSend, GeneticProgram **programList, int node);
//Get fitness values from the slave
void getFitnesses(int maxNum, GeneticProgram **programList); 

#endif
