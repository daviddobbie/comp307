/* File: main.c
 Author: Will Smart, 2004

 Description: the main procedure, that initializes and loops for evolution, also parses args
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include3 this file
            See the examples (eg Classify) for an example specialization
*/

#ifndef Headers

#include <stdlib.h>
#include <stdio.h>

#include "node.h"
#include "op.h"
#include "allc.h"
#include "pop.h"
#include "fit.h"
#include "rand.h"

#endif

#ifndef Variables

long g_relite;      // as percentages
long g_rmut;
long g_rcross;
long ngens,maxdep,mindep,imaxdep,imindep,seed,preach,maxnodes; // general control variables
long g_popSize;
long g_verbose;

#endif

#ifndef STRSTARTSWITH
#define STRSTARTSWITH(str,sta) ( ( strlen(str) >= strlen(sta) ) && !memcmp( str, sta, strlen(sta) ) )
#endif



//************************************************************************* Function: HelpScreen
// Args:          none
// Return value:  none
// Description: Display a help screen
#ifndef DHelpScreen
void HelpScreen(void) {
#else
void BaseHelpScreen(void) {
#endif
      if (POUT(1)) {
        fprintf(stderr,"Usage vgp [option] [option] ..\n ");
        fprintf(stderr,"  where option is \n");
        fprintf(stderr,"    mut:<real>         mutation rate          (default : 30)\n");
        fprintf(stderr,"    elite:<real>       elitism rate           (default : 10)\n");
        fprintf(stderr,"    slotsize:<real>    size of clsfy slots    (default : 0.25)\n");
        fprintf(stderr,"    gen:<int>          number of generations  (default : 50)\n");
        fprintf(stderr,"    pop:<int>          number in population   (default : 500)\n");
        fprintf(stderr,"    maxdep:<int>       maximum depth of tree  (default : 6)\n");
        fprintf(stderr,"    mindep:<int>       minimum depth of tree  (default : 3)\n");
        fprintf(stderr,"    initmaxdep:<int>   maximum depth of initial pop (default : 5)\n");
        fprintf(stderr,"    initmindep:<int>   minimum depth of initial pop (default : 3)\n");
        fprintf(stderr,"    patfn:<fn>         file with patterns     (default : pat.txt)\n");
        fprintf(stderr,"    ntourn:<int x>     number in tournament selection (default: 3)\n");
        fprintf(stderr,"    nnodes:<int x>     number of nodes in store (default: 1000000)\n");
        fprintf(stderr,"    prbest:<int x>     print best each x gen  (default : don\'t print)\n");
        fprintf(stderr,"    seed:<int x>       rand seed (or 0 for time) (default : 0)\n");
        fprintf(stderr,"    v:<int x>          verbose level of x (0-4) (default : 2)\n");
      }
}



//************************************************************************* Function: ParseArg
// Args:          Command line argument
// Return value: 0 on fail, 1 on succeed
// Description: Parse an argument
#ifndef DParseArg
long ParseArg(char *arg) {
#else
long BaseParseArg(char *arg) {
#endif
  if (STRSTARTSWITH(arg, "mut:")) g_rmut = atoi( arg + 4 );
  else if (STRSTARTSWITH(arg, "elite:")) g_relite = atoi( arg + 6 );
  else if (STRSTARTSWITH(arg, "slotsize:")) g_slotSize = atof( arg + 9 );
  else if (STRSTARTSWITH(arg, "gen:")) ngens = atoi( arg + 4 );
  else if (STRSTARTSWITH(arg, "maxdep:")) maxdep = atoi( arg + 7 );
  else if (STRSTARTSWITH(arg, "mindep:")) mindep = atoi( arg + 7 );
  else if (STRSTARTSWITH(arg, "initmaxdep:")) imaxdep = atoi( arg + 11 );
  else if (STRSTARTSWITH(arg, "initmindep:")) imindep = atoi( arg + 11 );
  else if (STRSTARTSWITH(arg, "pop:")) g_popSize = atoi( arg + 4 );
  else if (STRSTARTSWITH(arg, "seed:")) seed = atoi( arg + 5 );
  else if (STRSTARTSWITH(arg, "patfn:")) strcpy( g_patfn, arg + 6 );
  else if (STRSTARTSWITH(arg, "prbest:")) preach = atoi( arg + 7 );
  else if (STRSTARTSWITH(arg, "nnodes:")) maxnodes = atoi( arg + 7 );
  else if (STRSTARTSWITH(arg, "ntourn:")) g_numTourn = atoi( arg + 7 );
  else if (STRSTARTSWITH(arg, "v:")) g_verbose = arg[2]?atoi( arg + 2 ):3;
  else return(0);
  return(1);
}



//************************************************************************* Function: ParseArgs
// Args:          Command line
// Return value: 0 on fail, 1 on suceed
// Description: Parse the command line, filling variables
#ifndef DParseArgs
#define STRSTARTSWITH(str,sta) ( ( strlen(str) >= strlen(sta) ) && !memcmp( str, sta, strlen(sta) ) )
long ParseArgs(int argc, char *argv[]) {
#else
long BaseParseArgs(int argc, char *argv[]) {
#endif
  long i,bad=(argc==0)?1:0;
  g_rmut=30;
  g_relite=10;
  g_slotSize=0.25;
  ngens=50;
  maxdep=6;
  mindep=3;
  imaxdep=5;
  imindep=3;
  g_popSize=500;
  seed=100;
  *g_patfn=0;
  preach=1;
  maxnodes=1000000;
  g_numTourn=3;
  g_verbose=5;

  for (i = 1; (!bad)&&(i < argc); i++) if (!ParseArg(argv[i])) bad=1;
  if (bad) {
    HelpScreen();
    return(0);
  }
  return(1);
}




//************************************************************************* Function: DoEvolve
// Args:          none
// Description: Do one evolution
#ifndef DDoEvolve
void DoEvolve(void) {
#else
void BaseDoEvolve(void) {
#endif
  long gen,i,bstgen;
  long nel,nmut,trnum,vanum,tenum;
  char buf[10000],pbuf[10000],*pc;
  clock_t tim,tim2,timv;
  FILE *patfil;
  Pop *fpop=NULL,*tpop=NULL,pop1,pop2,*tempPop;

//  printf("%d %d %d %d %d %d\n",g_verbose,seed,imaxdep,imindep,maxdep,mindep);
  InitRand(seed);

  if (!InitFit()) return;

  // make the populations
  g_maxDepth=imaxdep;
  g_minDepth=imindep;
  fpop=&pop1;tpop=&pop2;
  //if (POUT(4)) printf("Initializing fpop..\n");
  InitPop(fpop,g_popSize);
  //if (POUT(4)) printf("Initializing tpop..\n");
  InitPop(tpop,g_popSize);
  PopRand(tpop,0,g_popSize);
  g_maxDepth=maxdep;
  g_minDepth=mindep;

  nel=g_relite*g_popSize/100;
  nmut=g_rmut*g_popSize/100;
  if (nmut+nel>g_popSize) nmut=g_popSize-nel;
  
  if (POUT(4)) printf("Elite:%d  Mut:%d  Cross:%d\n",nel,nmut,g_popSize-nel-nmut);

  g_evolDone=0;

// CalcFit(tpop->nodes[0],'p');

  for (gen=0;ngens&&!g_evolDone;gen++) {
    CalcPop(gen,tpop);
    if (g_evolDone||(gen==ngens)) break;

    tempPop=tpop;tpop=fpop;fpop=tempPop;
    PopElite(fpop,tpop,0,nel);
    PopMut(fpop,tpop,nel,nmut);
    PopCross(fpop,tpop,nel+nmut,g_popSize-nel-nmut);
 // PrintPop(tpop);
  }
  g_evolDone=1;

  PrintResults(gen,tpop);
  DelFit();

  DelPop(fpop);
  DelPop(tpop);
}

//************************************************************************* Function: IdealVal
// Args:          Command line
// Description: The main procedure for the program, this is a general base procedure that performs a single evolution
#ifndef Dmain
int main(int argc, char *argv[]) {
#else
int Basemain(int argc, char *argv[]) {
#endif
  long i;

  if (!ParseArgs(argc,argv)) exit(0);

  if (POUT(3)) {
   printf("Args OK : ");
   for ( i = 0; i < argc; i++ ) printf("%s ",argv[i]);
   printf("\n");
  }

  if (POUT(4)) printf("Initializing nodespace with %d nodes ..\n",maxnodes);
  if (!InitNodeStore(maxnodes)) {
    if (PERR) printf("Couldn't allocate nodespace\n");
    return(1);
  }

  InitOps();

  DoEvolve();
}
