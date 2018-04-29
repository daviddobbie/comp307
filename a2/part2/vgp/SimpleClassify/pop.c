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
long g_maxDepth=8;
long g_minDepth=2;
long g_numTourn=3;
Fit bestfit,bestva,vafit,tefit;
long bestgen,bestprog=0;
clock_t sttim,endtim,besttim;

//************************************************************************* Function: CalcPop
// Args:         gen: generation number
//               pop: population
// Return value: none
// Description:  any processing required for per generation
#define DCalcPop
void BaseCalcPop(long gen,Pop *pop);
void CalcPop(long gen,Pop *pop) {
  long acc;

  BaseCalcPop(gen,pop);

  if (!gen) {
    CLEARFIT(bestva);
    CLEARFIT(tefit);
    bestgen=0;
    besttim=sttim;
  }

  if (g_useVal) {
    vafit=CalcAcc(pop->nodes[bestprog],'v');
    if (FITBETTER(vafit,bestva)) {
      besttim=clock();
      bestva=vafit;
      tefit=CalcAcc(pop->nodes[bestprog],'s');
      bestgen=gen;
    }
  }
  else {
    vafit=CalcAcc(pop->nodes[bestprog],'s');
    if (FITBETTER(vafit,tefit)) {
      besttim=clock();
      tefit=vafit;
      bestgen=gen;
    }
  }
}

//************************************************************************* Function: PrintResults
// Args:         gen: final generation
// Return value: none
// Description:  print the results of the run
#define DPrintResults
void BasePrintResults(long gen,Pop *pop);
void PrintResults(long gen,Pop *pop) {
  char pbuf[10000];

  if (g_evolDone)
    if (POUT(3))
      printf("Final_test_acc: %f\nBest_val_acc: %f at_gen %d after %.2f seconds,_the_test_acc_was %f\n",
        CalcAcc(pop->nodes[bestprog],'s'),bestva.fitness,bestgen,
          ((double)(besttim-sttim))/((double)CLOCKS_PER_SEC),tefit.fitness);

  BasePrintResults(gen,pop);


}

// include the base procedures (except masked out ones)
#include "../src/pop.c"
