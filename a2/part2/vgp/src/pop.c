/* File: pop.c
 Author: Will Smart, 2004

 Description: Operations on populations of programs, eg. selection, genetic operators, initialization, etc..
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include this file
            See the examples (eg XOR) for an example specialization
*/

#ifndef Headers

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "pop.h"
#include "allc.h"
#include "op.h"
#include "rand.h"
#include "fit.h"

#endif

#ifndef Variables
double g_fullRate=0.5;
long g_maxDepth=8;
long g_minDepth=2;
long g_numTourn=3;
Fit bestfit;
long bestprog=0;
clock_t sttim,endtim;
#endif

extern long g_quit;

//************************************************************************* Function: CalcPop
// Args:         gen: generation number
//               pop: population
// Return value: none
// Description:  any processing required for per generation
#ifndef DNOCalcPop
#ifndef DCalcPop
void CalcPop(long gen,Pop *pop) {
#else
void BaseCalcPop(long gen,Pop *pop) {
#endif
  long i,ii,acc;
  if (!gen) {
    sttim=clock();
  }
  CLEARFIT(bestfit);
  for (i=0,bestprog=0;i<pop->num;i++) {
    pop->fits[i]=CalcAcc(pop->nodes[i],'r');
//      fprintf(stderr,"%.3f ",pop->fits[i].fitness);
    if (FITBETTER(pop->fits[i],bestfit)) {
      bestfit=pop->fits[i];
      bestprog=i;
    }
    if (pop->fits[i].fitness==BESTFIT) {
      g_evolDone=1;
    }
  }

  if (!g_evolDone) PrintResults(gen,pop);
}
#endif

//************************************************************************* Function: PrintResults
// Args:         gen: final generation
// Return value: none
// Description:  print the results of the run
#ifndef DNOPrintResults
#ifndef DPrintResults
void PrintResults(long gen,Pop *pop) {
#else
void BasePrintResults(long gen,Pop *pop) {
#endif
  if (g_evolDone) {
    char pbuf[10000];
    endtim=clock();
    if (POUT(6)) printf("\nEnd of Evolution\n\n");
    if (POUT(3))
      printf("Gens: %d  Final_fitness: %f  Took: %.2f seconds\n",
          gen, bestfit.fitness,((double)(endtim-sttim))/((double)CLOCKS_PER_SEC));
    if (POUT(4)) printf("Best Program: %s\n\n",PrintNodeSZ(pop->nodes[bestprog],NULL,pbuf,10000));
  }
  else
    if (POUT(5)) printf("Gen:%d  Best fitness:%.4f\n",gen,bestfit.fitness);
}
#endif

//************************************************************************* Function: InitPop
// Args:         pop: population to initialize
//               num: number of programs to put in pop
// Return value: 0 if error, 1 if succeed
// Description: Initializes a pop structure with a specified number of programs, initially all unknown terminals
#ifndef DNOInitPop
#ifndef DInitPop
long InitPop(Pop *pop,long num) {
#else
long BaseInitPop(Pop *pop,long num) {
#endif
  long i;
  pop->nodes=NULL;
  pop->fits=NULL;
  pop->num=0;
  if (!(pop->nodes=(Node**)mymalloc(sizeof(Node*)*num))) return(0);
  if (!(pop->fits=(Fit*)mymalloc(sizeof(Fit)*num))) {free(pop->nodes);pop->nodes=NULL;return(0);}
  pop->num=num;
  for (i=0;i<num;i++) {
    pop->nodes[i]=AllocNode();
    CLEARFIT(pop->fits[i]);
  }
  return(1);
}
#endif

//************************************************************************* Function: DelPop
// Args:         pop: population to destroy
// Return value: none
// Description: Deallocates a pop structure
#ifndef DNODelPop
#ifndef DDelPop
void DelPop(Pop *pop) {
#else
void BaseDelPop(Pop *pop) {
#endif
  long i;
  for (i=0;i<pop->num;i++) {
    ClearNode(pop->nodes[i]);
    DeAllocNode(pop->nodes[i]);
  }
  if (pop->nodes) {myfree(pop->nodes,sizeof(Node*)*pop->num);pop->nodes=NULL;}
  if (pop->fits) {myfree(pop->fits,sizeof(Fit)*pop->num);pop->fits=NULL;}
  pop->num=0;
}
#endif

//************************************************************************* Function: PopRand
// Args:         to: population
//               toInd: index of first program in population
//               toNum: number of programs from toInd
// Return value: none
// Description: Randomly generates toNum programs in the population from toInd. Full and Grow methods are used
#ifndef DNOPopRand
#ifndef DPopRand
void PopRand(Pop *to, long toInd, long toNum) {
#else
void BasePopRand(Pop *to, long toInd, long toNum) {
#endif
  long i;
  for (i=0;i<toNum;i++)
    if (RandUniform()<g_fullRate) GenFullNode(to->nodes[i+toInd],g_maxDepth);
    else GenGrowNode(to->nodes[i+toInd],g_minDepth,g_maxDepth);
}
#endif

//************************************************************************* Function: PopSelect
// Args:         pop: population
// Return value: The index of the selected individual
// Description: Selects an individual according to fitness (this just uses a very simple measure)
#ifndef DNOPopSelect
#ifndef DPopSelect
long PopSelect(Pop *pop) {
#else
long BasePopSelect(Pop *pop) {
#endif
  long i,a,b;
  b=RandInt(pop->num);
  for (i=0;i<g_numTourn-1;i++) {
    a=RandInt(pop->num);
    if (FITBETTER(pop->fits[a],pop->fits[b])) b=a;
  }
  return(b);
}
#endif

//************************************************************************* Function: PopElite
// Args:         pop: population to gen individuals from
//                to: population to put individuals into
//             toInd, toNum: the index and number of individuals in to
// Return value: none
// Description: Performs elitism, the best individuals in pop are copied (in order) into to
#ifndef DNOPopElite
#ifndef DPopElite
void PopElite(Pop *pop, Pop *to, long toInd, long toNum) {
#else
void BasePopElite(Pop *pop, Pop *to, long toInd, long toNum) {
#endif
  long i,ii,j,b;
  Node *node;
  for (i=0;i<toNum;i++) {
    b=-1;
    for (ii=0;ii<pop->num;ii++){
      if ((b<0)||FITBETTER(pop->fits[ii],pop->fits[b])) {
        for (j=0;j<i;j++) if (to->nodes[j+toInd]==pop->nodes[ii]) break;
        if (j==i) b=ii;
      }
    }
    ClearNode(to->nodes[i+toInd]);
    DeAllocNode(to->nodes[i+toInd]);
    to->nodes[i+toInd]=pop->nodes[b];
  }
  for (i=0;i<toNum;i++) {
    node=AllocNode();
    CopyNode(to->nodes[i+toInd],node);
    to->nodes[i+toInd]=node;
  }
}
#endif


//************************************************************************* Function: PopMut
// Args:         pop: population to gen individuals from
//                to: population to put individuals into
//             toInd, toNum: the index and number of individuals in to
// Return value: none
// Description: Performs mutation, individuals are selected, and branches mutated, into to
#ifndef DNOPopMut
#ifndef DPopMut
void PopMut(Pop *pop, Pop *to, long toInd, long toNum) {
#else
void BasePopMut(Pop *pop, Pop *to, long toInd, long toNum) {
#endif
  long i,ii,a,b,atdep,deep;
  Node *node;
  for (i=0;i<toNum;i++) {
    b=PopSelect(pop);
    a=i+toInd;
    ClearNode(to->nodes[a]);
    CopyNode(pop->nodes[b],to->nodes[a]);
    atdep=0;
    node=RandSubtree(to->nodes[a],g_maxDepth,1,g_maxDepth,&atdep,&deep);
    //node=MinDC(to->nodes[a],&atdep);// RandSubtree(to->nodes[a],g_maxDepth,1,g_maxDepth,&atdep,&deep);
    if (!node) {i--;continue;}
    ClearNode(node);
//    node->type='n';
//    node->value=0.1234;
    if (RandUniform()<g_fullRate) GenFullNode(node,g_maxDepth-atdep);
    else GenGrowNode(node,g_minDepth-atdep,g_maxDepth-atdep);

  }
}
#endif

//************************************************************************* Function: PopCross
// Args:         pop: population to gen individuals from
//                to: population to put individuals into
//             toInd, toNum: the index and number of individuals in to
// Return value: none
// Description: Performs crossover, individuals are selected, and branches transferred, into to
#ifndef DNOPopCross
#ifndef DPopCross
void PopCross(Pop *pop, Pop *to, long toInd, long toNum) {
#else
void BasePopCross(Pop *pop, Pop *to, long toInd, long toNum) {
#endif
  long i,ii,a,b,c,atdep,deep;
  Node *node,*fnode;
  for (i=0;i<toNum;i++) {
    c=PopSelect(pop);
    do {
      b=PopSelect(pop);
    } while (b==c);
    a=i+toInd;
    ClearNode(to->nodes[a]);
    CopyNode(pop->nodes[b],to->nodes[a]);
    node=RandSubtree(to->nodes[a],g_maxDepth,1,g_maxDepth,&atdep,&deep);
    if (!node) {i--;continue;}
    fnode=RandSubtree(pop->nodes[c],g_maxDepth,g_minDepth-atdep,g_maxDepth-atdep,&atdep,&deep);
    if (!fnode) {i--;continue;}
    ClearNode(node);
    CopyNode(fnode,node);


  }
}
#endif

//************************************************************************* Function: PrintPop
// Args:         pop: population to print
// Return value: none
// Description: Prints the whole population of programs
#ifndef DNOPrintPop
#ifndef DPrintPop
void PrintPop(Pop *pop) {
#else
void BasePrintPop(Pop *pop) {
#endif
  long i;
  char sz[10000];
  printf("Pop has %d\n",pop->num);
  for (i=0;i<pop->num;i++)
    printf("Prog %d : (%f)\n%s\n",i,pop->fits[i],PrintNodeSZ(pop->nodes[i],NULL,sz,10000));
}
#endif

