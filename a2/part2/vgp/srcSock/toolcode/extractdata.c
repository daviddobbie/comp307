
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

#define STRSTARTSWITH(str,sta) ( ( ( ( *str == ' ' ) && ( str++ ) ) || 1 ) && ( strlen(str) >= strlen(sta) ) && ( !memcmp( str, sta, strlen(sta) ) ) && ( str += strlen(sta) ) )

char g_exp[1000]="none";
char g_vars[10][100];

char *FindMark(char *buf,long buflen,char mark) {
  char *pc=buf;
  while (pc<buf+buflen) {
    if (((*pc>='a')&&(*pc<='z'))||((*pc>='A')&&(*pc<='Z'))) {
      if (*pc==mark) break;
      pc++;
    }
    else if (*pc=='"') {
      for (pc++;pc<buf+buflen;pc++) if (*pc=='"') break;
      if (*pc=='"') pc++;
    }
    else pc+=*pc+1;
  }
  if (pc<buf+buflen) return(pc);
  return(NULL);
}

void MakeExpLine(char *exp) {
  char *pc,*fpc;
  for (pc=exp,fpc=g_exp;*fpc;fpc++,pc++) {
    if ((*fpc=='%')&&(fpc[1]>='0')&&(fpc[1]<='9')&&(fpc[2]=='%')) {
      strcpy(pc,g_vars[fpc[1]-'0']);
      pc+=strlen(pc)-1;
      fpc+=2;
    }
    else *pc=*fpc;
  }
  *pc=0;
}

void AllData(void) {
  long at=-1,dat,dlen;
  char buf[100000],*pc,exp[1000];

  MakeExpLine(exp);
  while ((at=FindNextMatchingLine(at,exp,buf))!=-1) {
    do {
      pc=strchr(buf,'>');
      printf("exp %s%s",pc?pc+1:"?\n",(*buf=='*')?"done:":((*buf=='+')?"failed\n":"to be done\n"));
      if (*buf!='*') break;
      if (sscanf(buf+2,"%d %d",&dat,&dlen)<2) break;
      printf("(%d,%d) ",dat,dlen);
      if (!ReadDataFile(dat,dlen,buf)) break;

      pc=buf;
      while (pc<buf+dlen) {
        if (((*pc>='a')&&(*pc<='z'))||((*pc>='A')&&(*pc<='Z'))) {
          printf("%c:",*pc);
          pc++;
        }
        else if (*pc=='"') {
          printf("\"");
          for (pc++;pc<buf+dlen;pc++) {
            printf("%c",*pc);
            if (*pc=='"') break;
          }
          if (*pc=='"') pc++;
        }
        else {
          if (*pc==sizeof(double)) printf("%.4f ",*(double*)(pc+1));
          if (*pc==sizeof(long)) printf("%d ",*(long*)(pc+1));
          pc+=*pc+1;
        }
      }
      if (pc<buf+dlen) printf("Oversize\n");
      else printf("\n");
    } while(0);
  }
}

double AvgDouble(char mark,char field,long *pn) {
  long at=-1,dat,dlen,n=0;
  char buf[100000],*pc,exp[1000];
  double avg=0.0,d;

  MakeExpLine(exp);
  while ((at=FindNextMatchingLine(at,exp,buf))!=-1) {
    do {
      if (*buf!='*') break;
      if (sscanf(buf+2,"%d %d",&dat,&dlen)<2) break;
      if (!ReadDataFile(dat,dlen,buf)) break;
      if (!(pc=FindMark(buf,dlen,mark))) break;
      if ((mark!=field)&&!(pc=FindMark(pc,dlen-(pc-buf),field))) break;
      if (pc[1]!=sizeof(double)) break;
      d=*(double*)(pc+2);
      avg+=d;
      n++;
    } while(0);
  }
  if (pn) *pn=n;
  return(n?avg/n:0.0);
}

double AvgLong(char mark,char field,long *pn) {
  long at=-1,dat,dlen,n=0,l;
  char buf[100000],*pc,exp[1000];
  double avg=0.0;
  MakeExpLine(exp);
  while ((at=FindNextMatchingLine(at,exp,buf))!=-1) {
    do {
      if (*buf!='*') break;
      if (sscanf(buf+2,"%d %d",&dat,&dlen)<2) break;
      if (!ReadDataFile(dat,dlen,buf)) break;
      if (!(pc=FindMark(buf,dlen,mark))) break;
      if ((mark!=field)&&!(pc=FindMark(pc,dlen-(pc-buf),field))) break;
      if (pc[1]!=sizeof(long)) break;
      l=*(long*)(pc+2);
      avg+=l;
      n++;
    } while(0);
  }
  if (pn) *pn=n;
  return(n?avg/n:0.0);
}

void usage( char *ex ) {
    fprintf( stderr, "Usage : %s exp_file_prefix input_file \n", ex );
    exit(1);
}
void err( char *buf, char *pc ) {
    fprintf( stderr, "Error at : %s       point : %s\n", buf, pc );
    exit(3);
}



int main( int argc, char *argv[] )
{
  FILE *ifp;
  char ifn[200],efn[200],*pc,buf[1000],pstr[10]="%f";
  unsigned int len;
  long l,n,tn=0;
  double acc;
  int argn=1;

  if ( argn == argc)
    usage( argv[0] );

  strcpy(efn,argv[argn]);

  argn++;

  if ( argn == argc)
    usage( argv[0] );

  strcpy(ifn,argv[argn]);

  argn++;
  if ( argn != argc)
    usage( argv[0] );

  if ( (ifp = fopen(ifn, "r")) == NULL ) {
    fprintf( stderr, "Could not open file %s\n", ifn );
    exit(2);
  }

  if (!InitFiles(efn)) {
    fprintf( stderr, "Could not initialize files\n" );
    return(1);
  }

  while (pc=fgetln(ifp,&len)) {
    memcpy(buf,pc,len);
    if (buf[len-1]=='\n') len--;
    buf[len]=0;

    pc=buf;
    if (STRSTARTSWITH(pc,"printns ")) printf("%s",pc);
    if (STRSTARTSWITH(pc,"print ")) printf("%s ",pc);
    else if (STRSTARTSWITH(pc,"new line")) printf("\n");
    else if (STRSTARTSWITH(pc,"total number")) printf("%d",tn);
    else if (STRSTARTSWITH(pc,"exp ")) strcpy(g_exp,pc);
    else if (STRSTARTSWITH(pc,"var 0 ")) strcpy(g_vars[0],pc);
    else if (STRSTARTSWITH(pc,"var 1 ")) strcpy(g_vars[1],pc);
    else if (STRSTARTSWITH(pc,"var 2 ")) strcpy(g_vars[2],pc);
    else if (STRSTARTSWITH(pc,"var 3 ")) strcpy(g_vars[3],pc);
    else if (STRSTARTSWITH(pc,"var 4 ")) strcpy(g_vars[4],pc);
    else if (STRSTARTSWITH(pc,"var 5 ")) strcpy(g_vars[5],pc);
    else if (STRSTARTSWITH(pc,"var 6 ")) strcpy(g_vars[6],pc);
    else if (STRSTARTSWITH(pc,"var 7 ")) strcpy(g_vars[7],pc);
    else if (STRSTARTSWITH(pc,"var 8 ")) strcpy(g_vars[8],pc);
    else if (STRSTARTSWITH(pc,"var 9 ")) strcpy(g_vars[9],pc);
    else if (STRSTARTSWITH(pc,"string for print ")) strcpy(pstr,pc);
    else if (STRSTARTSWITH(pc,"final time")) {printf(pstr,AvgDouble('e','t',&n));tn+=n;}
    else if (STRSTARTSWITH(pc,"final test acc %")) {printf(pstr,100.0*AvgDouble('e','t',&n));tn+=n;}
    else if (STRSTARTSWITH(pc,"final gen")) {printf(pstr,AvgLong('e','e',&n));tn+=n;}
    else if (STRSTARTSWITH(pc,"best val %")) {printf(pstr,100.0*AvgDouble('b','v',&n));tn+=n;}
    else if (STRSTARTSWITH(pc,"time at best val")) {printf(pstr,AvgDouble('b','t',&n));tn+=n;}
    else if (STRSTARTSWITH(pc,"test acc at best val %")) {printf(pstr,100.0*AvgDouble('b','a',&n));tn+=n;}
    else if (STRSTARTSWITH(pc,"gen at best val")) {printf(pstr,AvgLong('b','b',&n));tn+=n;}
    else if (STRSTARTSWITH(pc,"all data")) AllData();
  }
  fclose(ifp);
}
