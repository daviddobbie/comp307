#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../src/pop.h"
#include "../src/allc.h"
#include "../src/op.h"
#include "../src/rand.h"
#include "../src/fit.h"

#define Headers
void PropNode(Node *node, char cset);
void ReClassify(Pop *pop, char cset);
//Fit CalcFit(Node *node, char cset);

#define Variables
double g_fullRate=0.5;
long g_maxDepth=8;
long g_minDepth=2;
long g_numTourn=3;
Fit bestfit,bestva,vafit,tefit;
long bestgen,bestprog=0;
clock_t sttim,endtim,besttim;
long g_reclsGens=5;

#define POUTS(i) (((g_verbose/100)%100)>=i)

extern double g_rate;
extern char g_useProped;
extern int g_fitType;

extern int g_consock;

void WriteOutput(char *buf,long buflen) {
  if ( write( g_consock, buf, buflen ) < 0 )
    perror("sending message");
}

char *AppendString(char *buf,char *str) {strcpy(buf,str);return(buf+strlen(buf));}
char *AppendDouble(char *buf,double d) {*buf=(char)sizeof(double);*(double*)(buf+1)=d;return(buf+1+sizeof(double));}
char *AppendLong(char *buf,long l) {*buf=(char)sizeof(long);*(long*)(buf+1)=l;return(buf+1+sizeof(long));}


//************************************************************************* Function: PrintResults
// Args:         gen: final generation
// Return value: none
// Description:  print the results of the run
#define DPrintResults
void BasePrintResults(long gen,Pop *pop);
void PrintResults(long gen,Pop *pop) {
  char pbuf[10000],buf[10000],*pc;

  if (g_evolDone) {
    endtim=clock();
    if (POUT(3))
    printf("Final_test_acc: %f\nBest_val_acc: %f at_gen %d after %.2f seconds,_the_test_acc_was %f\n",
      CalcAcc(pop->nodes[bestprog],'s'),bestva.fitness,bestgen,
        ((double)(besttim-sttim))/((double)CLOCKS_PER_SEC),tefit.fitness);
    if (POUTS(3)) {
      pc=buf;
      pc=AppendString(pc,"e");pc=AppendLong(pc,gen);
      pc=AppendString(pc,"f");pc=AppendDouble(pc,bestfit.fitness);
      pc=AppendString(pc,"t");pc=AppendDouble(pc,((double)(endtim-sttim))/((double)CLOCKS_PER_SEC));
      pc=AppendString(pc,"a");pc=AppendDouble(pc,CalcAcc(pop->nodes[bestprog],'s').fitness);
      pc=AppendString(pc,"b");pc=AppendLong(pc,bestgen);
      pc=AppendString(pc,"v");pc=AppendDouble(pc,bestva.fitness);
      pc=AppendString(pc,"a");pc=AppendDouble(pc,tefit.fitness);
      //printf("b:%d s:%d\n",besttim,sttim);
      pc=AppendString(pc,"t");pc=AppendDouble(pc,((double)(besttim-sttim))/((double)CLOCKS_PER_SEC));
      WriteOutput(buf,pc-buf);
    }
    if (POUTS(4)) {
      pc=buf;
      PrintNodeSZ(pop->nodes[0],NULL,pbuf,10000);
      pc=AppendString(pc,"p\"");pc=AppendString(pc,pbuf);pc=AppendString(pc,"\"");
      WriteOutput(buf,pc-buf);
    }
  }
  else {
    if (POUTS(5)) {
      pc=buf;
      pc=AppendString(pc,"g");pc=AppendLong(pc,gen);pc=AppendString(pc,"f");pc=AppendDouble(pc,bestfit.fitness);
      WriteOutput(buf,pc-buf);
    }
  }

  BasePrintResults(gen,pop);

}
