/* File: allc.h
 Author: Will Smart, 2004

 Description: header file for allc.c, node allocation

*/
#ifndef allch
#define allch

#include "common.h"
#include "node.h"

// NodeStore: contains a fast-access block of nodes for allocation/deallocation
struct NodeStore {
  long arrSize;           // size of block (in nodes)
  Node *arr;              // Node block
  char *used;             // array indicating which nodes are allocated
  long *free,freeIndex;   // stack to reference nodes ready for allocation
};
typedef struct NodeStore NodeStore;

extern long g_totMalloc;

// in allc.c
long InitNodeStore(long size);  // call before use
void DeleteNodeStore();         // call after use
void DeAllocNode(Node *node);
Node *AllocNode();

#endif
