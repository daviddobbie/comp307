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

#define DNodeCorrect
//************************************************************************* Function: NodeCorrect
// Args:    node: the root of a program (which has been evaluated)
//          pat : the pattern to use
// Return value: 0 if program did not guess pattern's class, 1 if it did
// Description: This function returns a value dependent on whether the program correctly calculates the class of a pattern
long NodeCorrect(Node *node, Pat *pat) {
  if (pat->cls==0) return(node->value<=0);
  else return(node->value>0);
}

#define DLoadSet
//************************************************************************* Function: LoadSet
// Args:     fn: filename
//          set: set structure to fill
//          setStr : the string with the layout of sets (eg. "rsv")
//          thisSet : the character this set uses in the above string (eg 's')
// Return value: number of patterns in set, or -1 on error
// Description: Loads a set of patterns from a file, allocating new memory if neccesary
long LoadSet(FILE *fil,Set *set,char *setStr,char thisSet) {
  long fsiz,foff,ncls,nfeat,i,ii,j,l;
  set->num=4;
  set->nfeat=2;
  set->pats=(Pat*)mymalloc(sizeof(Pat)*set->num);
  for (i=0;i<set->num;i++) {
    set->pats[i].fv=(Feat*)mymalloc(sizeof(Feat)*set->nfeat);
    switch (i) {
      case 0: set->pats[i].cls=0;set->pats[i].fv[0].value=0;set->pats[i].fv[1].value=0;break;
      case 1: set->pats[i].cls=1;set->pats[i].fv[0].value=1;set->pats[i].fv[1].value=0;break;
      case 2: set->pats[i].cls=1;set->pats[i].fv[0].value=0;set->pats[i].fv[1].value=1;break;
      case 3: set->pats[i].cls=0;set->pats[i].fv[0].value=1;set->pats[i].fv[1].value=1;break;
    }
  }
  g_numFeat=set->nfeat;
  g_numCls=2;
  return(set->num);
}

#define NOFEATSCALE

// include the base procedures (except masked out ones)
#include "../src/fit.c"
