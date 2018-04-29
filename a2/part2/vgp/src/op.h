/* File: op.h
 Author: Will Smart, 2004

 Description: header file for op.c, declares functions

*/


#ifndef oph
#define oph
#include "common.h"
#include "node.h"

void GenFullNode(Node *node, long depth);
void GenGrowNode(Node *node, long mindepth, long maxdepth);
Node *RandSubtree(Node *node, long maxdepth, long mindeep, long maxdeep, long *patdep, long *pdeep);
#endif
