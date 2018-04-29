/* File: node.c
 Author: Will Smart, 2004

 Description: specialized node procedures, adds a sin function

*/

#include <stdio.h>
#include <math.h>

#include "../src/allc.h"
#include "../src/node.h"
#include "../src/rand.h"
#include "../src/fit.h"
#define Headers

#define EVALMACRO_8(node,fv,a1,a2,a3) (sin(a1))

//************************************************************************* Function: PrintSin
// Args:         as for print
// Return value: the start of the buffer (for printf, etc..)
// Description: Prints the word sin into a buffer
char *PrintSin(Node *node,Feat *featArr,char *buf,long buflen) {
  if (buflen<=3) return(NULL);
  strcpy(buf,"sin");
  return(buf);
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
  l=g_numOps;
  g_ops[l].macro=8;g_ops[l].type='s';g_ops[l].nargs=1;g_ops[l].print=PrintSin;l++;// the new bit, a sin function
  g_numOps=l;
}

// include the base procedures (except masked out ones)
#include "../src/node.c"
