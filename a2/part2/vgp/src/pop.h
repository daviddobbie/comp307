/* File: pop.h
 Author: Will Smart, 2004

 Description: header file for pop.c, has Pop structure, and some extern vars, functions

*/


#ifndef poph
#define poph

#include "common.h"
#include "node.h"
#include "fit.h"

#ifndef PopStruct
#define PopStruct
struct Pop {          // structure for a population, includes a block of root nodes, and a block of the fitnesses
  Node **nodes;
  Fit *fits;
  long num;
};
typedef struct Pop Pop;
#endif

extern long g_maxDepth;    // current maximum program generation/operation depth
extern long g_minDepth;    //         minimum
extern double g_fullRate;  // rate of full vs. grow, i.e. 0.5 = half-half
extern long g_numTourn;   // number used for tournament selection

long InitPop(Pop *pop,long num);
void DelPop(Pop *pop);
void CalcPop(long gen,Pop *pop);
void PrintResults(long gen,Pop *pop);
void PopElite(Pop *pop, Pop *to, long toInd, long toNum);
void PopMut(Pop *pop, Pop *to, long toInd, long toNum);
void PopCross(Pop *pop, Pop *to, long toInd, long toNum);
void PopRand(Pop *to, long toInd, long toNum);
void PrintPop(Pop *pop);
long PopSelect(Pop *pop);
#endif
