/* File: allc.c
 Author: Will Smart, 2004

 Description: Handles allocation of nodes for all programs, removes need to use system allocation
    calls for nodes, as they all come from a single large block

*/

#include <stdlib.h>
#include <stdio.h>

#include "allc.h"

long g_totMalloc=0;

NodeStore ns;     // see allc.h
                  // this currently holds all nodes, however multiple nodestores are possible with
                  // changes to some functions in this file.

//************************************************************************* Function: mymalloc
// Args:     siz: the size of the block to allocate
// Return value: a pointer to the block
// Description: Allocate a block of memory
void *mymalloc(long siz) {
  void *ret;
  ret=malloc(siz);
  if (ret) g_totMalloc+=siz;
  return(ret);
}

//************************************************************************* Function: myfree
// Args:     ptr: the block to free
//           siz: the size of the block
// Return value: none
// Description: Deallocate a block of memory
void myfree(void *ptr,long siz) {
  free(ptr);
  g_totMalloc-=siz;
}

//************************************************************************* Function: InitNodeStore
// Args:     size: the size of the node block (i.e. max number of nodes that can be allocated)
// Return value: 0 on fail, 1 on succeed
// Description: Initialize ns (above) with a specified number of nodes
long InitNodeStore(long size) {
  long i;
  ns.arrSize=0;
  ns.arr=NULL;
  ns.used=NULL;
  ns.free=NULL;
  if (!((ns.arr=(Node*)mymalloc(sizeof(Node)*size))&&
      (ns.free=(long*)mymalloc(sizeof(long)*size))&&
      (ns.used=(char*)mymalloc(sizeof(char)*size)))) {
    DeleteNodeStore();
    return(0);
  }
  ns.arrSize=size;
  for (i=0;i<size;i++) {    // some initialization:
    ns.free[i]=i;           // free list points to whole array
    ns.used[i]=0;           // no nodes are used
  }
  ns.freeIndex=size-1;      // free index points to top of stack
  return(1);
}

//************************************************************************* Function: DeleteNodeStore
// Args: none
// Return value: none
// Description: free memory of ns
void DeleteNodeStore() {
  if (ns.arr) myfree(ns.arr,sizeof(Node)*ns.arrSize);
  if (ns.free) myfree(ns.free,sizeof(long)*ns.arrSize);
  if (ns.used) myfree(ns.used,sizeof(char)*ns.arrSize);
  ns.arrSize=0;
  ns.arr=NULL;
  ns.free=NULL;
  ns.used=NULL;
}

//************************************************************************* Function: DeAllocNode
// Args: a pointer to a node (previously gained by calling AllocNode)
// Return value: none
// Description: Return an allocated node to the store
void DeAllocNode(Node *node) {
  long l=(long)((char*)node-(char*)(ns.arr));       // bytes from pointer to array base
  if ((l<0)||(l%((long)sizeof(Node)))) {            // i.e. if pointer before array, or on an odd byte
    if (PERR) fprintf(stderr,"Attempt to deallocate non existant node (1)\n");
    return;
  }
  l=l/((long)sizeof(Node));                         // nodes from pointer to start of array
  if (l>=ns.arrSize) {                              // i.e. if pointer after array
    if (PERR) fprintf(stderr,"Attempt to deallocate non existant node (2)\n");
    return;
  }
  if (ns.used[l]==0) {                              // i.e. node wasn't previously allocated
    if (PERR) fprintf(stderr,"Attempt to deallocate unused node (1)\n");
    return;
  }
  ns.used[l]=0;                                     // return node to array
  ns.free[++ns.freeIndex]=l;
}

//************************************************************************* Function: AllocNode
// Args: none
// Return value: a pointer to a (fairly blank) node structure
// Description: Allocate a node for use as a program part,
//  all allocated nodes should come back with DeAllocNode, not doing so is a memory leak.
Node *AllocNode() {
  Node *ret;
  int i;
  if (ns.freeIndex<0) {                             // i.e. no nodes left in array
    if (PERR) fprintf(stderr,"Cannot allocate node, no memory\n");
    return(NULL);
  }
  ns.used[ns.free[ns.freeIndex]]=1;                 // allocate node by: set node used
  ret=ns.arr+ns.free[ns.freeIndex--];               //         pop stack with pointer
  ret->nargs=0;                                     //         node initially is a terminal
  return(ret);
}
