/* File: node.h
 Author: Will Smart, 2004

 Description: node header file

*/

#ifndef nodeh
#define nodeh

#include "common.h"

// define these in the common.h, as required
#ifndef MAXARG    // maximum number of arguments per node
#define MAXARG 3
#endif

#ifndef Ret       // the type of the node output (eg. double or long or whatever)
#define Ret double
#define RetPrintStr ".6f"
#define RetParseStr "lf"
#endif

#ifndef RetParseStr
#define RetParseStr RetPrintStr
#endif

#ifndef MAXOPS
#define MAXOPS 20
#endif

#ifndef BASICALLY_ZERO
#define BASICALLY_ZERO 0.00001
#endif


#ifndef NodeStructs
struct Feat {   // feature structure
  Ret value;
};
typedef struct Feat Feat;

struct FeatNI {  // Feature reference
  long featIndex;
};
typedef struct FeatNI FeatNI;

struct Node {   // the node structure, the same for terminals and functions, (terminals have nargs==0)
  Ret value;      // the evaluated value of the node
  Ret *values;
  char op;      // operation of node
  long nargs;     // number of arguments of the node
  struct Node *args[MAXARG]; // the references to the arguments (for functions)
  union {         // this is a general space for node info, currently only features use it
    struct FeatNI feat;
  } info;
};
typedef struct Node Node;
#endif

#ifndef OpStructs
struct Operation {
  char macro,type;
  long nargs;
  Ret (*funcNArr)(Node *node,Feat **featArr,long fvSize,Ret **to,long *toSize);
  Ret (*funcN)(Node *node,Feat *featArr);
  char * (*print)(Node *node,Feat *featArr,char *buf,long buflen);
  char * (*scan)(Node *node, char *buf);
  void (*rand)(Node *node);
};
typedef struct Operation Operation;
#endif

extern Operation g_ops[MAXOPS];
extern long g_numOps;

// node.c
void InitOps(void);
char *ScanStd(Node *node, char *buf);
void RandStd(Node *node);
char *PrintStd(Node *node,Feat *featArr,char *buf,long buflen);
Ret EvaluateNode(struct Node *node,struct Feat *featArr);
int EvaluateNodeToArr(Node *node,Feat **fvArr,long fvSize,Ret **to,long *toSize);
char *PrintNodeSZ(struct Node *node, struct Feat *featArr, char *buf, long buflen);
void ClearNode(struct Node *node);
char *ParseSZ(struct Node *node, char *buf);
void CopyNode(struct Node *node, struct Node *to);
long RandParam(Node *node, long ufunc, long uterm);
Ret FailValue(void);

#endif
