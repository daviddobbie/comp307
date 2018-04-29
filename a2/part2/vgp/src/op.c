/* File: op.c
 Author: Will Smart, 2004

 Description: Some simple operations on programs, such as growing and selecting nodes at random
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include this file
            See the examples (eg XOR) for an example specialization
*/

#ifndef Headers

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "node.h"
#include "rand.h"
#include "allc.h"
#include "fit.h"

#endif

#define MAXSTACK 20


#ifndef DGenFullNode
//************************************************************************* Function: GenFullNode
// Args:         node: branch of program to generate from
//              depth: depth of branch to generate
// Return value: none
// Description: A simple recursive procedure to generate a program using full
void GenFullNode(Node *node, long depth) {
  long si=0, ai[MAXSTACK], n;
  Node *stk[MAXSTACK];
  if (node->nargs) ClearNode(node);
  n=RandParam(node,depth>1,depth<=1);
  for (n--;n>=0;n--) {
    node->args[n]=AllocNode();
    node->args[n]->nargs=0;
    GenFullNode(node->args[n],depth-1);
  }
}
#endif

#ifndef DGenGrowNode
//************************************************************************* Function: GenGrowNode
// Args:         node: branch of program to generate from
//              mindepth: minimum depth of branch to generate
//              maxdepth: maximum depth of branch to generate
// Return value: none
// Description: A simple recursive procedure to generate a program using grow
void GenGrowNode(Node *node, long mindepth, long maxdepth) {
  long si=0, ai[MAXSTACK], n;
  Node *stk[MAXSTACK];
  if (node->nargs) ClearNode(node);
  n=RandParam(node,maxdepth>1,mindepth<=1);
  for (n--;n>=0;n--) {
    node->args[n]=AllocNode();
    node->args[n]->nargs=0;
    GenGrowNode(node->args[n],mindepth-1, maxdepth-1);
  }
}
#endif

#ifndef DNodeSize
//************************************************************************* Function: NodeSize
// Args:         node: branch of program to size
// Return value: number of nodes in the program branch
// Description: A recursive procedure to find the size of a program
long NodeSize(Node *node) {
  long ret=1,i;
  for (i=0;i<node->nargs;i++) ret+=NodeSize(node->args[i]);
  return(ret);
}

#endif

#ifndef DNodeAt
//************************************************************************* Function: NodeAt
// Args:         node: branch of program to go from
//                  i: index of desired node
// Return value: the node at the specified index
// Description: A recursive procedure to find a node in a tree (use in conjunction with NodeSize to find a random node
Node *NodeAt(Node *node,long i) {
  Node *ret;
  long ii;
  if (i<=1) return(node);
  for (ii=0;ii<node->nargs;ii++) {
    ret=NodeAt(node->args[i],--i);
    if (ret) return(ret);
  }
  return(NULL);
}
#endif

#ifndef DNodeSizeWith
//************************************************************************* Function: NodeSizeWith
// Args:         node: branch of program to size
//                adep: allowable depth, i.e. do not consider nodes deeper in the program than this
//                maxdeep: maximum subtree depth, i.e. do not consider nodes deeper (to the furthest leaf) than this
//                mindeep: minimum subtree depth, i.e. do not consider nodes shallower (to the furthest leaf) than this
//                atdep: the current depth in the main program (call with 0)
//                pdeep: pointer to a long that recieves the depth of the subtree (call with a pointer to some long)
// Return value: number of nodes in the program branch that fit the criteria
// Description: A recursive procedure to find the number of nodes of a program that fit within some constraints
long NodeSizeWith(Node *node, long adep, long maxdeep, long mindeep, long atdep, long *pdeep) {
  long ret=0,i,bdeep=0,deep,dep;
  for (i=0;i<node->nargs;i++) {
    ret+=NodeSizeWith(node->args[i],adep,maxdeep,mindeep,atdep+1,&deep);
    if (bdeep<deep) bdeep=deep;
  }
  *pdeep=bdeep+1;
  if ((atdep<adep)&&(*pdeep<=maxdeep)&&(*pdeep>=mindeep))
    ret++;
  return(ret);
}
#endif

#ifndef DNodeAtWith
//************************************************************************* Function: NodeAtWith
// Args:         node: branch of program to find node in
//                  i: pointer to a long with the (0 based) index of the node to find (the value is destroyed)
//                adep: allowable depth, i.e. do not consider nodes deeper in the program than this
//                maxdeep: maximum subtree depth, i.e. do not consider nodes deeper (to the furthest leaf) than this
//                mindeep: minimum subtree depth, i.e. do not consider nodes shallower (to the furthest leaf) than this
//                atdep: the current depth in the main program (call with 0)
//                pdeep: pointer to a long that recieves the depth of the subtree (call with a pointer to some long)
// Return value: pointer to node of index *i in the program branch, considering only nodes that fit the criteria
// Description: A recursive procedure to find a nodes in a program considering nodes that fit within some constraints
//            (use in conjunction with NodeSizeWith to find a random node in the tree, with criteria)
Node *NodeAtWith(Node *node, long *i, long adep, long maxdeep, long mindeep, long *atdep, long *pdeep) {
  long ii,bdeep=0,deep,dep;
  Node *ret;
  for (ii=0;ii<node->nargs;ii++) {
    dep=(*atdep)+1;
    ret=NodeAtWith(node->args[ii],i,adep,maxdeep,mindeep,&dep,&deep);
    if (ret) {
      *pdeep=deep;
      *atdep=dep;
      return(ret);
    }
    if (bdeep<deep) bdeep=deep;
  }
  *pdeep=bdeep+1;
  if ((*atdep<adep)&&(*pdeep<=maxdeep)&&(*pdeep>=mindeep)&&((*i)--<=0))
    return(node);
  return(NULL);
}
#endif

#ifndef DRandSubtree
//************************************************************************* Function: RandSubtree
// Args:         node: program to find node in
//                maxdepth: allowable depth, i.e. do not consider nodes deeper in the program than this
//                mindeep: minimum subtree depth, i.e. do not consider nodes shallower (to the furthest leaf) than this
//                maxdeep: maximum subtree depth, i.e. do not consider nodes deeper (to the furthest leaf) than this
//                patdep: filled with the depth in the program of the selected node (0 based)
//                pdeep: filled with depth of the subtree (eg. 1 for terminal)
// Return value: pointer a random node in the tree, that fits the criteria
// Description: Returns a node in the program provided, the node is selected randomly from those nodes that fit
//            the various criteria of depth in program and depth of subtree
Node *RandSubtree(Node *node, long maxdepth, long mindeep, long maxdeep, long *patdep, long *pdeep) {
  long siz,i,a,b,c;
  Node *ret;
  siz=NodeSizeWith(node,maxdepth, maxdeep, mindeep,0,&b);
  if (siz==0) return(NULL);
  i=RandInt(siz);
  a=0;
  ret=NodeAtWith(node,&i,maxdepth, maxdeep, mindeep,&a,&c);
  *patdep=a;
  *pdeep=b;
  return(ret);
}
#endif
