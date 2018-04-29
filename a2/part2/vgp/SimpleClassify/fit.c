/* File: fit.c
 Author: Will Smart, 2004

 Description: specialized fitness procedures

*/
#define Headers     // stop ../src/fit.c from including the headers

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../src/fit.h"
#include "../src/allc.h"
#include "../src/rand.h"

int g_useVal=0;
Set trainSet,testSet,valSet;
char g_setstr[100]="rvs";

#define SETFROMCHAR(ch) ((ch=='s')?&testSet:((ch=='v')?&valSet:&trainSet))

#define DInitFit
//************************************************************************* Function: InitFit
// Args:    none
// Return value: none
// Description: Initialization of fitness stuff
int InitFit() {
  long trnum,tenum,vanum;
  FILE *patfil;
  Set *sets[3];

  // load patterns from file, or atleast call loadset
  if (*g_patfn) {
    if ((!(patfil=fopen(g_patfn,"r")))&&PERR) {fprintf(stderr,"Error: Could not open pattern file %s.\n",g_patfn);return(0);}
  }
  else {fprintf(stderr,"Error: Must have a pattern file!\n");return(0);}

  trainSet.num=testSet.num=valSet.num=0;
  if (((trnum=LoadSet(patfil,&trainSet,g_setstr,'r'))==-1)||
      ((tenum=LoadSet(patfil,&testSet,g_setstr,'s'))==-1)||
      ((vanum=LoadSet(patfil,&valSet,g_setstr,'v'))==-1)) {
    if (PERR) fprintf(stderr,"Error: Loading validation set\n");
    DelSet(&trainSet);
    DelSet(&testSet);
    DelSet(&valSet);
    if (patfil) fclose(patfil);
    return(0);
  };
  if (patfil) fclose(patfil);
  if (valSet.num) g_useVal=1;

  if (POUT(3)) printf("Sets: training has %d, test has %d, validation has %d\n\n",trnum,tenum,vanum);

  //  do any scaling and initialization required
  sets[0]=&trainSet;
  sets[1]=&testSet;
  sets[2]=&valSet;
  if (!InitSets(sets,3)) {if (PERR) fprintf(stderr,"Error: initializing sets\n");return(0);};
  return(1);
}

#define DDelFit
//************************************************************************* Function: DelFit
// Args:    none
// Return value: none
// Description: Deallocate fitness stuff
void DelFit(void) {
  DelSet(&trainSet);
  DelSet(&testSet);
  DelSet(&valSet);
}


// include the base procedures (except masked out ones)
#include "../src/fit.c"
