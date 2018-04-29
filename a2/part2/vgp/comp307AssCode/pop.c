/* File: pop.c
 Author: Will Smart, 2004

 Description: Operations on populations of programs, eg. selection, genetic operators, initialization, etc..
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include this file
            See the examples (eg XOR) for an example specialization
*/

#define Headers

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../src/pop.h"
#include "../src/allc.h"
#include "../src/op.h"
#include "../src/rand.h"
#include "../src/fit.h"


#define Variables
double g_fullRate=0.5;
long g_maxDepth=7;
long g_minDepth=2;
long g_numTourn=3;
Fit bestfit,bestva,vafit,tefit;
long bestgen,bestprog=0;
clock_t sttim,endtim,besttim;

double CalcFit(Node *node);

//************************************************************************* Function: CalcPop
// Args:         gen: generation number
//               pop: population
// Return value: none
// Description:  any processing required for per generation
#define DCalcPop
void CalcPop(long gen,Pop *pop) {
  long i,ii,acc;
  Fit bad;
  if (!gen) {
    sttim=clock();
  }
  CLEARFIT(bestfit);
  CLEARFIT(bad);
  for (i=0,bestprog=0;i<pop->num;i++) {
    pop->fits[i].fitness=CalcFit(pop->nodes[i]);
    if (FITBETTER(bad,pop->fits[i])) pop->fits[i].fitness=bad.fitness;
    if (pop->fits[i].fitness<AIMMSE) {
      g_evolDone=1;
    }
    if (FITBETTER(pop->fits[i],bestfit)) {
      bestfit=pop->fits[i];
      bestprog=i;
    }
  }

  if (!g_evolDone) PrintResults(gen,pop);
}


// include the base procedures (except masked out ones)
#include "../src/pop.c"
