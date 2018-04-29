/* File: fit.c
 Author: Will Smart, 2004

 Description: specialized fitness procedures for symbolic regression

*/

#define Headers     // stop ../src/fit.c from including the headers

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../src/fit.h"
#include "../src/allc.h"
#include "../src/rand.h"

#define STRTX -10.0
#define ENDX 10.0
#define STEPX 0.1
#define FUNC(x) x*x+sin(x-0.4567)

#define MAXTMPRET 1000000
Ret g_tmpRetArr[MAXTMPRET];

#define DCalcFit
//************************************************************************* Function: CalcFit
// Args:    node: root of program to calculate fitness for
//         pats, numPats: not used here
// Return value: A fitness structure filled with the fitness of the program
// Description: Calculates the fitness of the program by calculating the MSE of the program, compared to the target
//          over a specified interval
double CalcFit(Node *node) {
  Feat *fv[500],fva[500];
  double x,y,sse=0.0,num=0.0;
  long i,tonum=MAXTMPRET,ii;
  Ret *to=g_tmpRetArr;
  for (i=0,x=STRTX;x<=ENDX;i++,x+=STEPX,num+=1.0) {fva[i].value=x;fv[i]=fva+i;}
  ii=i;
  EvaluateNodeToArr(node,fv,i,&to,&tonum);
  for (i=0,x=STRTX;i<ii;x+=STEPX,i++) {
    y=FUNC(x);
    sse+=(y-node->values[i])*(y-node->values[i]);
  }
  return(sse/num);
}
/*
double CalcFit(Node *node) {
  Feat fv[1];
  double x,y,sse=0.0,num=0.0;
  for (x=STRTX,num=0;x<=ENDX;x+=STEPX,num+=1.0) {
    y=FUNC(x);
    fv[0].value=x;
    EvaluateNode(node,fv);
    sse+=(y-node->value)*(y-node->value);
  }
  return(sse/num);
}
*/

#define DLoadSet
//************************************************************************* Function: LoadSet
// Args:     fn: filename
//          set: set structure to fill
//          setStr : the string with the layout of sets (eg. "rsv")
//          thisSet : the character this set uses in the above string (eg 's')
// Return value: number of patterns in set, or -1 on error
// Description: Loads a set of patterns from a file, allocating new memory if neccesary
long LoadSet(FILE *fil,Set *set,char *setStr,char thisSet) {
  g_numFeat=1;
  set->num=0;
  set->nfeat=1;
  set->pats=NULL;
  return(0);
}

// include the base procedures (except masked out ones)
#include "../src/fit.c"
