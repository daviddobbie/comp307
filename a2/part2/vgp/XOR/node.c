/* File: node.c
 Author: Will Smart, 2004

 Description: specialized node procedures

*/

#include <stdio.h>
#include <math.h>

#include "../src/allc.h"
#include "../src/node.h"
#include "../src/rand.h"
#include "../src/fit.h"
#define Headers


#define DRandStd
//************************************************************************* Function: RandStd
// Args:         node: a node to randomly assign
// Return value: none, node filled
// Description: This function randomly sets a node to be an already chosen type of primitive
void RandStd(Node *node) {
  switch (g_ops[node->op].type) {
    case 'n': node->value=1;break;
    case 'f': node->info.feat.featIndex=RandInt(g_numFeat);break;
  }
}

#define DInitOps
//************************************************************************* Function: InitOps
// Args:         none
// Return value: none, g_ops filled
// Description: Sets the operations to be used for evaluation, etc..
//              g_ops is filled with pointers to the operations
void BaseInitOps(void);
void InitOps(void) {
  long l;
  BaseInitOps();
  for (l=0;l<g_numOps;l++) if (g_ops[l].type=='%') {g_ops[l].nargs=-1;break;}
}


// include the base procedures (except masked out ones)
#include "../src/node.c"
