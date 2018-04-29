/* File: fit.c
 Author: Will Smart, 2004

 Description: Fitness related procedures, basic classification version
          This file is to be used as a general base set of procedures for the fitness procedures.
            It is rigged for classification using SRS as the classification strategy.
            Procedures include those: to load patterns from the type of image pattern file I use,
              to initialize (empty), to calculate fitness and accuracy (pretty much the same here),
              to check if a node is correct using SRS, and to ReClassify (empty as SRS needs none).
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include this file
            See the examples (eg XOR) for an example specialization
*/

#ifndef Headers       // define this to prevent a repeat

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fit.h"
#include "allc.h"
#include "rand.h"

#endif

long g_numCls=4;              // the number of classes, change this in LoadPats or InitFit to the correct figure
double g_slotSize=1.0;        // the space between classes
long g_evolDone=0;
long g_numFeat=4;
Set mainSet;
char g_patfn[256]="";

#ifndef MAXTMPRET
#define MAXTMPRET 1000000
Ret g_tmpRetArr[MAXTMPRET];
#endif

#ifndef MAXVAL
#define MAXVAL 1000.0
#endif

#ifndef SETFROMCHAR
#define SETFROMCHAR(ch) (&mainSet)
#endif

//************************************************************************* Function: InitFit
// Args:    none
// Return value: none
// Description: Initialization of fitness stuff
#ifndef DNOInitFit
#ifndef DInitFit
int InitFit() {
#else
int BaseInitFit() {
#endif
  long num;
  FILE *patfil;
  Set *sets[1];
  // load patterns from file, or atleast call loadset
  if (*g_patfn) {
    if ((!(patfil=fopen(g_patfn,"r")))&&PERR) {fprintf(stderr,"Error: Could not open pattern file %s.\n",g_patfn);return(0);}
  }
  else patfil=NULL;

  mainSet.num=0;
  if ((num=LoadSet(patfil,&mainSet,"r",'r'))==-1) {
    if (PERR) fprintf(stderr,"Error: Loading set\n");
    DelSet(&mainSet);
    if (patfil) fclose(patfil);
    return(0);
  }
  if (patfil) fclose(patfil);

  if (POUT(3)) printf("Set has %d patterns\n\n",num);

  //  do any scaling and initialization required
  sets[0]=&mainSet;
  if (!InitSets(sets,1)) {if (PERR) fprintf(stderr,"Error: initializing sets\n");return(0);};
  return(1);
}
#endif
//************************************************************************* Function: DelFit
// Args:    none
// Return value: none
// Description: Deallocate fitness stuff
#ifndef DNODelFit
#ifndef DDelFit
void DelFit(void) {
#else
void BaseDelFit() {
#endif
  DelSet(&mainSet);
}
#endif

//************************************************************************* Function: CalcAcc
// Args:    node: root of program to calculate accuracy for
//         set: set of patterns to use
// Return value: A fitness structure filled with the accuracy of the program
// Description: Calculate the accuracy of the program at node using the patterns in pats
#ifndef DNOCalcAcc
#ifndef DCalcAcc
Fit CalcAcc(Node *node, char cset) {
#else
Fit BaseCalcAcc(Node *node, char cset) {
#endif

  Fit ret;
  Ret *to=g_tmpRetArr;
  long acc,ii,tonum=MAXTMPRET;
  Set *set=SETFROMCHAR(cset);
  acc=0;
  CLEARFIT(ret);
  if (!EvaluateNodeToArr(node,set->fvs,set->num,&to,&tonum)) return(ret);
  for (ii=0;ii<set->num;ii++) {
    node->value=node->values[ii];
    if (NodeCorrect(node,set->pats+ii)) acc++;
  }
  ret.fitness=set->num?((double)acc)/set->num:0.0;  // accuracy
  return(ret);
}
/*
  Fit ret;
  long acc,ii;
  Set *set=SETFROMCHAR(cset);
  acc=0;
  for (ii=0;ii<set->num;ii++) {
    EvaluateNode(node,set->pats[ii].fv);
    if (NodeCorrect(node,set->pats+ii)) acc++;
  }
  ret.fitness=set->num?((double)acc)/set->num:0.0;  // accuracy
  return(ret);
}
*/
#endif

//************************************************************************* Function: NodeCorrect
// Args:    node: the root of a program (which has been evaluated)
//          pat : the pattern to use
// Return value: 0 if program did not guess pattern's class, 1 if it did
// Description: This function returns a value dependent on whether the program correctly calculates the class of a pattern
#ifndef DNONodeCorrect
#ifndef DNodeCorrect
long NodeCorrect(Node *node, Pat *pat) {
#else
long BaseNodeCorrect(Node *node, Pat *pat) {
#endif
  return(((long)(node->value/g_slotSize+g_numCls/2.0)==pat->cls)?1:0); // SRS
}
#endif


//************************************************************************* Function: LoadSet
// Args:     fil: file pointer
//          set: set structure to fill
//          setStr : the string with the layout of sets (eg. "rsv")
//          thisSet : the character this set uses in the above string (eg 's')
// Return value: number of patterns in set, or -1 on error
// Description: Loads a set of patterns from a file, allocating new memory if neccesary
#ifndef DNOLoadSet
#ifndef DLoadSet
long LoadSet(FILE *fil,Set *set,char *setStr,char thisSet) {
#else
long BaseLoadSet(FILE *fil,Set *set,char *setStr,char thisSet) {
#endif
  char buf[1000],*pc;
  unsigned int len;
  long fsiz,foff,ncls,i,ii,j,l,n,ln;
  double d;

  set->num=0;
  set->nfeat=0;
  set->pats=NULL;

  if (!fil) return(-1);

  for (i=n=0;setStr[i];i++) if (setStr[i]==thisSet) n++;
  if (!n) return(0);

  do {
//    if ((fseek(fil,0,SEEK_SET)==-1)||!(pc=fgetln(fil,&len))) {if (PERR) fprintf(stderr,"Could not get first line in pattern file\n");break;}
//    memcpy(buf,pc,len);buf[len]=0;
    if ((fseek(fil,0,SEEK_SET)==-1)||!fgets(buf,1000,fil)) {if (PERR) fprintf(stderr,"Could not get first line in pattern file\n");break;}
    if (sscanf(buf,"%d %d %d %d",&fsiz,&foff,&ncls,&set->nfeat)<4)
      {if (PERR) fprintf(stderr,"Could not get first four numbers in pattern file\n");break;}

    if ((fsiz%strlen(setStr))&&PERR) fprintf(stderr,"Warning: Set %c will not divide evenly into pattern file with this set string (%s)\n",thisSet,setStr);

    set->num=(fsiz/strlen(setStr))*n;
    set->fvs=(Feat**)mymalloc(sizeof(Feat*)*set->num);
    set->pats=(Pat*)mymalloc(sizeof(Pat)*set->num);
    for (i=0;i<set->num;i++) set->pats[i].fv=NULL;

    ln=2;n=0;
    for (i=0;setStr[i];i++) {
      for (ii=0;ii<fsiz/strlen(setStr);ii++,ln++) {
//        if (!(pc=fgetln(fil,&len))) {if (PERR) fprintf(stderr,"Could not get line %d in pattern file\n",ln);break;}
//        memcpy(buf,pc,len);buf[len]=0;
        if (!fgets(buf,1000,fil)) {if (PERR) fprintf(stderr,"Could not get line %d in pattern file\n",ln);break;}
        if (setStr[i]!=thisSet) continue;

        if (sscanf(buf,"%s %d %d %d %d %d %s %n",set->pats[n].fn,&set->pats[n].x,&set->pats[n].y,
            &set->pats[n].wide,&set->pats[n].high,&set->pats[n].cls,set->pats[n].clsnm,&l)<7)
          {if (PERR) fprintf(stderr,"Could not get values in line %d of pattern file\n",ln);break;}
        pc=buf+l;

        set->pats[n].fv=set->fvs[n]=(Feat*)mymalloc(sizeof(Feat)*set->nfeat);

        for (j=0;j<set->nfeat;j++) {
          if (sscanf(pc,"%lf%n",&d,&l)<1)
            {if (PERR) fprintf(stderr,"Could not get feature value %d in line %d of pattern file\n",j,ln);break;}
          set->pats[n].fv[j].value=(Ret)d;
          pc+=l;
        }
        n++;
      }
      if (ii<fsiz/strlen(setStr)) break;
    }
    if (setStr[i]) break;
    if (n!=set->num) {if (PERR) fprintf(stderr,"Error in LoadPats, pattern numbers do not agree (%d vs %d)\n",n,set->num);break;}


    
    g_numFeat=set->nfeat;
    g_numCls=ncls;

    return(n);
  } while (0);
  DelSet(set);
  return(-1);
}
#endif

//************************************************************************* Function: DelSet
// Args:    set: set to deallocate
// Return value: none
// Description: deallocates a set
#ifndef DNODelSet
#ifndef DDelSet
void DelSet(Set *set) {
#else
void BaseDelSet(Set *set) {
#endif
  long i;
  if (!(set->pats&&set->num)) return;
  for (i=0;i<set->num;i++)
    if (set->pats[i].fv) {myfree(set->pats[i].fv,sizeof(Feat)*set->nfeat);set->pats[i].fv=NULL;}
  myfree(set->pats,sizeof(Pat)*set->num);
  set->pats=NULL;
  set->num=0;
  set->nfeat=0;
}
#endif

//************************************************************************* Function: InitSets
// Args:    sets: array of sets
//          numSets: number in array
// Return value: 1 if succeed, 0 if fail
// Description: initializes the sets, mainly scales them
#ifndef DNOInitSets
#ifndef DInitSets
long InitSets(Set **sets,long numSets) {
#else
long BaseInitSets(Set **sets,long numSets) {
#endif
  long i,ii,j,s,fst;
  double fMin,fMax;
  j=0;
  for (i=0;i<numSets;i++) if (sets[i]->pats) {
    if (j>0) {
      if (sets[i]->nfeat!=j) {
        if (PERR) fprintf(stderr,"Error: All sets must have the same number of features..\n");
        return(0);
      }
    }
    else j=sets[i]->nfeat;
  }
#ifndef NOFEATSCALE
  for (j=0;j<sets[0]->nfeat;j++) {
    fst=1;
    for (s=0;s<numSets;s++) if (sets[s]->pats) {
      for (i=0;i<sets[s]->num;i++,fst=0) {
        if (fst||(fMin>sets[s]->pats[i].fv[j].value)) fMin=sets[s]->pats[i].fv[j].value;
        if (fst||(fMax<sets[s]->pats[i].fv[j].value)) fMax=sets[s]->pats[i].fv[j].value;
      }
    }
    for (s=0;s<numSets;s++) if (sets[s]->pats) {
      for (i=0;i<sets[s]->num;i++)
        sets[s]->pats[i].fv[j].value=((sets[s]->pats[i].fv[j].value-fMin)/(fMax-fMin)-0.5)*2.0;
    }
  }
#endif
  return(1);
}
#endif
