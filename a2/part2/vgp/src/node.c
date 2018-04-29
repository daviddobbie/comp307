/* File: node.c
 Author: Will Smart, 2004

 Description: Node related procedures, basic functions and terminals version
          This file is to be used as an example for creating a primitive set.
            In this set the terminals are Numeric (double) and Features.
            The functions are +, -, *, / (protected) and if<0 (3 arg)
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include this file
            See the examples (eg XOR) for an example specialization
*/


#ifndef Headers

#include <stdio.h>
#include <math.h>

#include "allc.h"
#include "node.h"
#include "rand.h"
#include "fit.h"

#endif

#ifndef Variables
Operation g_ops[MAXOPS];
long g_numOps;
#endif

#ifndef EVALMACRO_1
#define EVALMACRO_1(node,fv,a1,a2,a3) (node->value)
#endif
#ifndef EVALMACRO_2
#define EVALMACRO_2(node,fv,a1,a2,a3) (fv[node->info.feat.featIndex].value)
#endif
#ifndef EVALMACRO_3
#define EVALMACRO_3(node,fv,a1,a2,a3) (a1+a2)
#endif
#ifndef EVALMACRO_4
#define EVALMACRO_4(node,fv,a1,a2,a3) (a1-a2)
#endif
#ifndef EVALMACRO_5
#define EVALMACRO_5(node,fv,a1,a2,a3) (a1*a2)
#endif
#ifndef EVALMACRO_6
#define EVALMACRO_6(node,fv,a1,a2,a3) ((a1<0)?a2:a3)
#endif
#ifndef EVALMACRO_7
#define EVALMACRO_7(node,fv,a1,a2,a3) ((fabs(tmp1=a2)<BASICALLY_ZERO)?0:(a1/tmp1))
#endif
#ifndef EVALMACRO_8
#define EVALMACRO_8(node,fv,a1,a2,a3) (FailValue())
#endif
#ifndef EVALMACRO_9
#define EVALMACRO_9(node,fv,a1,a2,a3) (FailValue())
#endif
#ifndef EVALMACRO_10
#define EVALMACRO_10(node,fv,a1,a2,a3) (FailValue())
#endif

//************************************************************************* Function: FailValue
// Args:         none
// Return value: 0
// Description: Prints an error message
#ifndef DFailValue
Ret FailValue(void) {
  if (PERR) fprintf(stderr,"Error while evaluating, probably a bad operator macro.\n");
  exit(0);
  return(0);
}
#endif


//************************************************************************* Function: EvaluateNode
// Args:         node: branch of program to evaluate
//              featArr: The array of features to use
// Return value: the evaluated value of the branch
// Description: A simple recursive procedure to find the value of a program with a set of features
#ifndef DNOEvaluateNode
#ifndef DEvaluateNode
Ret EvaluateNode(Node *node,Feat *featArr) {
#else
Ret BaseEvaluateNode(Node *node,Feat *featArr) {
#endif
long i;
  Ret tmp1,tmp2;
  //if (node->valok) return(node->value);
  switch (g_ops[node->op].macro) {
    case 0:
      if (g_ops[node->op].funcN) {
        for (i=0;i<node->nargs;i++) EvaluateNode(node->args[i],featArr);
        node->value = g_ops[node->op].funcN(node,featArr);
      }
      else return(FailValue());
      break;
    case 1: node->value=EVALMACRO_1(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 2: node->value=EVALMACRO_2(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 3: node->value=EVALMACRO_3(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 4: node->value=EVALMACRO_4(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 5: node->value=EVALMACRO_5(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 6: node->value=EVALMACRO_6(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 7: node->value=EVALMACRO_7(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 8: node->value=EVALMACRO_8(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 9: node->value=EVALMACRO_9(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    case 10: node->value=EVALMACRO_10(node,featArr,EvaluateNode(node->args[0],featArr),EvaluateNode(node->args[1],featArr),EvaluateNode(node->args[2],featArr));break;
    default: node->value=FailValue();break;
  }
#ifndef NOCHECKNAN
  if (PERR&&isnan(node->value)) {                           // this was a problem for a while
    fprintf(stderr,"%c:%" RetPrintStr ",",g_ops[node->op].type,node->value);exit(0);
  }
#endif
  return(node->value);
}
#endif

//************************************************************************* Function: EvaluateNodeToArr
// Args:         node: branch of program to evaluate
//              fvArr: The array of pointers of feature vectors
//              fvSize: The number of feature vectors
//              to : array of Rets to fill
//              toSize : number of rets in array
// Return value: pointer to the evaluated values of the branch
// Description: A simple recursive procedure to find the value of a program with a set of features
#ifndef DNOEvaluateNodeToArr
#ifndef DEvaluateNodeToArr
int EvaluateNodeToArr(Node *node,Feat **fvArr,long fvSize,Ret **to,long *toSize) {
#else
int BaseEvaluateNodeToArr(Node *node,Feat **fvArr,long fvSize,Ret **to,long *toSize) {
#endif
  long i,ii;
  Feat *featArr;
  Ret tmp1,tmp2;
  Ret *args[MAXARG];
  if (*toSize<fvSize) {
    if (PERR) fprintf(stderr,"Error: run out of room in EvaluateNodeToArr\n");
    return(0);
  }
  node->values=*to;
  (*to)+=fvSize;
  (*toSize)-=fvSize;
  for (i=0;i<node->nargs;i++) if (!EvaluateNodeToArr(node->args[i],fvArr,fvSize,to,toSize)) return(0);else args[i]=node->args[i]->values;
  for (;i<MAXARG;i++) args[i]=node->values;// just filler for macros
  
//  fprintf(stderr,"op %d  ",node->op);
  switch (g_ops[node->op].macro) {
    case 0:
      if (g_ops[node->op].funcNArr) g_ops[node->op].funcNArr(node,fvArr,fvSize,to,toSize);
      else if (g_ops[node->op].funcN) for (i=0;i<fvSize;i++) {
        for (ii=0;ii<node->nargs;ii++) node->args[ii]->value=node->args[ii]->values[i];
        node->values[i]=g_ops[node->op].funcN(node,fvArr[i]);
      }
      else {
        fprintf(stderr,"Operator %d has no macro, or function, in EvaluateNodeToArr\n",node->op);
        FailValue();
        return(0);
      }
      break;
    case 1: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_1(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 2: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_2(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 3: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_3(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 4: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_4(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 5: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_5(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 6: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_6(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 7: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_7(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 8: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_8(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 9: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_9(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    case 10: for (i=0;i<fvSize;i++) node->values[i]=EVALMACRO_10(node,fvArr[i],args[0][i],args[1][i],args[2][i]);break;
    default: FailValue();return(0);
  }
  return(1);
}
#endif

//************************************************************************* Function: PrintNodeSZ
// Args:         node: program root
//              featArr: The array of features to use
//              buf,buflen: A character array to print string to
// Return value: buf (for use in printf or sim
// Description: Print the program at node to the string at buf without using more than buflen characters.
#ifndef DNOPrintNodeSZ
#ifndef DPrintNodeSZ
char *PrintNodeSZ(Node *node, Feat *featArr, char *buf, long buflen) {
#else
char *BasePrintNodeSZ(Node *node, Feat *featArr, char *buf, long buflen) {
#endif
  long i,l;
  char tbuf[32],*st=buf,*pc;
  if (node->nargs) {
    if (buflen<=1) return(NULL);
    *(buf++)='(';*buf=0;buflen--;
  }
  if (!g_ops[node->op].print(node,featArr,buf,buflen)) return(NULL);
  l=strlen(buf);
  buf+=l;buflen-=l;
  for (i=0;i<node->nargs;i++) {
    if (buflen<=1) return(NULL);
    *(buf++)=' ';*buf=0;buflen--;
    if (!PrintNodeSZ(node->args[i],featArr,buf,buflen)) return(NULL);
    l=strlen(buf);
    buflen-=l;buf+=l;
  }
  if (node->nargs) {
    if (buflen<=1) return(NULL);
    *(buf++)=')';*buf=0;buflen--;
  }
  return(st);
}
#endif

//************************************************************************* Function: ClearNode
// Args:         node: program branch
// Return value: none
// Description: Reduce the program at node to only one node (the root) and set as an unknown terminal
//          This procedure should be called whenever deleting subtrees, as it DeAlloc's nicely
#ifndef DNOClearNode
#ifndef DClearNode
void ClearNode(Node *node) {
#else
void BaseClearNode(Node *node) {
#endif
  long i;
  for (i=0;i<node->nargs;i++) if (node->args[i]) {
    ClearNode(node->args[i]);
    DeAllocNode(node->args[i]);
  }
  node->nargs=0;
  node->op=0;
}
#endif

//************************************************************************* Function: ParseSZ
// Args:         node: program root (terminal) to put program in
//              buf: A zero-tem string containing printed program
// Return value: NULL if error in string, otherwise end of read buffer
// Description: Parses buf for a program, which it grows from node
#ifndef DNOParseSZ
#ifndef DParseSZ
char *ParseSZ(Node *node, char *buf) {
#else
char *BaseParseSZ(Node *node, char *buf) {
#endif
  char *st=buf,typ,*pc;
  long i;
  if (*st=='(') {
    st++;
    for (i=0;i<g_numOps;i++)
      if ((g_ops[i].nargs>0)&&(*st==g_ops[i].type)) break;
    if (i==g_numOps) {
      if (PERR) fprintf(stderr,"Unknown function (%c) in parse\n",*st);
      return(NULL);
    }
    node->op=i;
    node->nargs=g_ops[i].nargs;
    while (*st&&(*st!=' ')) st++;
    if (!*st) {fprintf(stderr,"Unexpected end to string (1), in parse\n");return(NULL);}
    for (i=0;i<node->nargs;i++) {
      st++;
      if (!*st) {fprintf(stderr,"Unexpected end to string (2), in parse\n");return(NULL);}
      node->args[i]=AllocNode();
      if (!(st=ParseSZ(node->args[i],st))) {node->op=0;return(NULL);}// should really dealloc
    }
    if (*st!=')') {
      if (PERR) fprintf(stderr,"No end paranthesis for function\n");
      return(NULL);
    }
    st++;    
  }
  else {
    if ((*st=='-')||((*st>='0')&&(*st<='9'))) typ='n';
    else typ=*st;
    for (i=0;i<g_numOps;i++)
      if ((g_ops[i].nargs==0)&&(typ==g_ops[i].type)) break;
    if (i==g_numOps) {
      if (PERR) fprintf(stderr,"Unknown terminal (%c) in parse\n",typ);
      return(NULL);
    }
    node->op=i;
    node->nargs=0;
    if (!(st=g_ops[node->op].scan(node,st))) return(NULL);
  }
  return(st);
}
#endif

//************************************************************************* Function: CopyNode
// Args:         node: program root to copy from
//                to: terminal node to copy tree to
// Return value: none
// Description: Duplicates a program, note that to should be a terminal node (eg. use ClearNode)
#ifndef DNOCopyNode
#ifndef DCopyNode
void CopyNode(Node *node, Node *to) {
#else
void BaseCopyNode(Node *node, Node *to) {
#endif
  long i;
  *to=*node;
  for (i=0;i<node->nargs;i++) {
    to->args[i]=AllocNode();
    CopyNode(node->args[i],to->args[i]);
  }
}
#endif

//************************************************************************* Function: RandParam
// Args:         node: a node to randomly assign
//              ufunc: 0 to not consider functions, 1 to consider functions
//              uterm: 0 to not consider terminals, 1 to consider terminals
// Return value: number of arguments of the node (i.e. 0 for terminals)
// Description: This function randomly sets a node to be some kind of primitive, with any internal params required
#ifndef DNORandParam
#ifndef DRandParam
long RandParam(Node *node, long ufunc, long uterm) {
#else
long BaseRandParam(Node *node, long ufunc, long uterm) {
#endif
  long i,ii,nf=0,nt=0;
  float d;
  for (i=0;i<g_numOps;i++)
    if (g_ops[i].nargs==0) nt++;
    else if (g_ops[i].nargs>0) nf++;
  if (ufunc&&uterm) i=RandInt(nf+nt);
  else if (ufunc) i=RandInt(nf);
  else i=RandInt(nt)+nf;
  if (i<nf) {
    for (ii=0;ii<g_numOps;ii++) if ((g_ops[ii].nargs>0)&&(i--==0)) break;
    node->op=ii;
  }
  else {
    i-=nf;
    for (ii=0;ii<g_numOps;ii++) if ((g_ops[ii].nargs==0)&&(i--==0)) break;
    node->op=ii;
  }
  node->nargs=g_ops[node->op].nargs;
  g_ops[node->op].rand(node);

  return(node->nargs);
}
#endif

//************************************************************************* Function: PrintStd
// Args:         node: node to print
//              featArr: The array of features to use
//              buf,buflen: A character array to print string to
// Return value: buf (for use in printf or sim
// Description: Print the node to the string at buf without using more than buflen characters.
//        This prints the standard operators
#ifndef DNOPrintStd
#ifndef DPrintStd
char *PrintStd(Node *node,Feat *featArr,char *buf,long buflen) {
#else
char *BasePrintStd(Node *node,Feat *featArr,char *buf,long buflen) {
#endif
  char *st=buf,tbuf[16];
  switch (g_ops[node->op].type) {
    case 'f':
      sprintf(tbuf,"f%d",node->info.feat.featIndex);
      if (featArr) sprintf(tbuf+strlen(tbuf),"{%" RetPrintStr "}",featArr[node->info.feat.featIndex].value);
      if (buflen<=strlen(tbuf)) return(NULL);
      strcpy(buf,tbuf);
      break;
    case 'n':
      sprintf(tbuf,"%" RetPrintStr,node->value);
      if (buflen<=strlen(tbuf)) return(NULL);
      strcpy(buf,tbuf);
      break;
    case 'i':
      if (buflen<=4) return(NULL);
      strcpy(buf,"if<0");
      break;
    default:
      if (buflen<=1) return(NULL);
      *(buf++)=g_ops[node->op].type;*buf=0;
      break;
  }
  return(st);
}
#endif

//************************************************************************* Function: ScanStd
// Args:         node: The node to fill
//              buf: A zero-tem string containing printed node
// Return value: NULL if error in string, otherwise end of read buffer
// Description: Parses buf for a node
#ifndef DNOScanStd
#ifndef DScanStd
char *ScanStd(Node *node, char *buf) {
#else
char *BaseScanStd(Node *node, char *buf) {
#endif
  int len;
  switch (g_ops[node->op].type) {
    case 'f':
      if (sscanf(buf,"f%d%n",&node->info.feat.featIndex,&len)<1) {
        if (PERR) fprintf(stderr,"Bad feature string in scan\n");
        return(NULL);
      }
      buf+=len;
      break;
    case 'n':
      if (sscanf(buf,"%" RetParseStr "%n",&node->value,&len)<1) {
        if (PERR) fprintf(stderr,"Bad numeric string in scan\n");
        return(NULL);
      }
      buf+=len;
      break;
    default:
      if (PERR) fprintf(stderr,"Unknown terminal type (%c) in scan\n",g_ops[node->op].type);
      return(NULL);
  }
  return(buf);
}
#endif

//************************************************************************* Function: RandStd
// Args:         node: a node to randomly assign
// Return value: none, node filled
// Description: This function randomly sets a node to be an already chosen type of primitive
#ifndef DNORandStd
#ifndef DRandStd
void RandStd(Node *node) {
#else
void BaseRandStd(Node *node) {
#endif
  switch (g_ops[node->op].type) {
    case 'n': node->value=RandOne();break;
    case 'f': node->info.feat.featIndex=RandInt(g_numFeat);/*fprintf(stderr,"(F%d)",node->info.feat.featIndex);*/break;
  }
}
#endif

//************************************************************************* Function: five standard functions
// Args:         up to three arguments to function
// Return value: Return value of function/terminal
// Description: The standard functions, used in the initial system
#ifndef StdFunctions
Ret Div(Node *node,Feat *featArr) {
  return((fabs((double)node->args[1]->value)<BASICALLY_ZERO)?0:(node->args[0]->value/node->args[1]->value));
}
#endif


//************************************************************************* Function: InitOps
// Args:         none
// Return value: none, g_ops filled
// Description: Sets the operations to be used for evaluation, etc..
//              g_ops is filled with pointers to the operations
#ifndef DNOInitOps
#ifndef DInitOps
void InitOps(void) {
#else
void BaseInitOps(void) {
#endif
  long l;
  for (l=0;l<MAXOPS;l++) {
    g_ops[l].macro=0;g_ops[l].type=0;
    g_ops[l].nargs=0;g_ops[l].funcN=NULL;
    g_ops[l].print=PrintStd;g_ops[l].scan=ScanStd;g_ops[l].rand=RandStd;
  }
  l=0;
  g_ops[l].macro=10;g_ops[l].type='?';g_ops[l].nargs=-1;l++; // (-1 means this operator is never assigned)
  g_ops[l].macro=1;g_ops[l].type='n';l++;
  g_ops[l].macro=2;g_ops[l].type='f';l++;
  g_ops[l].macro=3;g_ops[l].type='+';g_ops[l].nargs=2;l++;
  g_ops[l].macro=4;g_ops[l].type='-';g_ops[l].nargs=2;l++;
  g_ops[l].macro=5;g_ops[l].type='*';g_ops[l].nargs=2;l++;
  g_ops[l].macro=7;g_ops[l].type='%';g_ops[l].nargs=2;l++;
  g_ops[l].macro=6;g_ops[l].type='i';g_ops[l].nargs=3;l++;
  g_numOps=l;
}
#endif
