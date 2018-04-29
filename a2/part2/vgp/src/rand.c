/* File: rand.c
 Author: Will Smart, 2004

 Description: Some random functions
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include this file
            See the examples (eg XOR) for an example specialization
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h"

#ifndef DInitRand
//************************************************************************* Function: InitRand
// Args:         seed: seed to give generator
// Return value: none
// Description: Initializes the random number generator
void InitRand(long seed) {
  srandom(seed);
}
#endif

#ifndef DRandUniform
//************************************************************************* Function: RandUniform
// Args: none
// Return value: random number between 0 and 1
// Description: Generates a random number between 0 and 1
float RandUniform() {
  float ret;
  long i;
  i=random()%10000000L;
  ret=i/10000000.0;
if (PERR&&isnan(ret))
  fprintf(stderr,"bad1:%f,",ret);
//ret/=(unsigned long)(0x7FFFFFFFL);
//if (isnan(ret))
//  printf(":%f,",ret);
return(ret);
}
#endif

#ifndef DRandOne
//************************************************************************* Function: RandOne
// Args: none
// Return value: random number between -1 and 1
// Description: Generates a random number between -1 and 1
float RandOne() {
  float ret,d=15000.0;
  long i;
  i=(random()%30000L)-15000;
  ret=i;
  ret/=d;
  if (PERR&&isnan(ret))
    fprintf(stderr,"bad1:%f,",ret);
//ret/=(unsigned long)(0x7FFFFFFFL);
//if (isnan(ret))
//  printf(":%f,",ret);
return(ret);
}
#endif

#ifndef DRandInt
//************************************************************************* Function: RandInt
// Args:      mod: number of possible return numbers
// Return value: random integer between 0 and mod-1
// Description: Generates a random integer between 0 and mod-1
long RandInt(long mod) {
  return(random()%mod);
}
#endif


#ifndef DRandNormal
//************************************************************************* Function: RandNormal
// Args:      mean,sd:mean and standard deviation
// Return value: random double in toe gaussian distribution
// Description: Generates a random real in a gaussian distribution
double RandNormal(double mean,double sd) {
  double u1,u2,r,theta,v,pi=3.141592654;
  u1 = RandUniform();
  u2 = RandUniform();
  r = sqrt(-2.0*log(u1));
  theta =2.0*pi*u2;
  v = r*cos(theta);
// v2= r*sin(theta);
  return(sd*v+mean);
}
#endif
