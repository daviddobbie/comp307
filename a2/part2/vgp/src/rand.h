/* File: rand.h
 Author: Will Smart, 2004

 Description: Declares functions in rand.c, for random number generation

*/

#ifndef randh
#define randh

#include "common.h"

void InitRand(long seed);
double RandUniform();
double RandOne();
long RandInt(long mod);
double RandNormal(double mean,double sd);

#endif
