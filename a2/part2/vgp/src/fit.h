/* File: fit.h
 Author: Will Smart, 2004

 Description: fitness header file

*/


#ifndef fith
#define fith

#include "common.h"
#include "node.h"

// define these in the specialized common.h if they need changing
#ifndef FITBETTER
#define FITBETTER(fa,fb) (fa.fitness>fb.fitness)
#endif

#ifndef CLEARFIT
#define CLEARFIT(fa) fa.fitness=0.0;
#endif

#ifndef BESTFIT
#define BESTFIT 1.0
#endif

#ifndef PROPORTIONALFIT
#define PROPORTIONALFIT(fa) fa.fitness
#endif

#ifndef FitStruct
struct Fit { // very simple structure for fitness
  double fitness;
};
typedef struct Fit Fit;
#endif

#ifndef PatStruct
struct Pat { // pattern for object classification, though it will do others
  char fn[32];
  long x,y,wide,high;
  long cls;
  double tempd;
  char clsnm[8];
  Feat *fv;
};
typedef struct Pat Pat;
#endif

#ifndef SetStruct
struct Set { // a set of patterns
  long num;
  long nfeat;
  Pat *pats;
  Feat **fvs;
};
typedef struct Set Set;
#endif


extern long g_numCls;   // number of classes
extern long g_evolDone; // set to exit evolution
extern double g_slotSize; // the size of slots in srs,sdrs and the minimum size of regions in cdrs
extern long g_numFeat;  // the current number of features per pattern
extern int g_useVal;
extern char g_patfn[256];

//fit.c
int InitFit(void);
void DelFit(void);
long NodeCorrect(Node *node, Pat *pat);
long LoadSet(FILE *fil,Set *set, char *setStr, char thisSet);
void DelSet(Set *set);
long InitSets(Set **sets,long numSets);
Fit CalcAcc(Node *node, char cset);

#endif
