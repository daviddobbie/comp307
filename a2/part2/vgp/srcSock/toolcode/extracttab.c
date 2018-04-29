
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

#define STRSTARTSWITH(str,sta) ( ( ( ( *str == ' ' ) && ( str++ ) ) || 1 ) && ( strlen(str) >= strlen(sta) ) && ( !memcmp( str, sta, strlen(sta) ) ) && ( str += strlen(sta) ) )

#define MAXEXP 6
#define MAXCOL 20

char g_exp[MAXEXP][1000];
int g_expInd=1;
char g_vars[10][100];
char g_pstr[10]="%.4f";
char g_pstr2[10]="%.4f";


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

void MakeExpLine(char *exp,char vars[10][100]) {
  char *pc,*fpc;
  for (pc=exp,fpc=g_exp[g_expInd];*fpc;fpc++,pc++) {
    if ((*fpc=='%')&&(fpc[1]>='0')&&(fpc[1]<='9')&&(fpc[2]=='%')) {
      strcpy(pc,*vars[fpc[1]-'0']?vars[fpc[1]-'0']:g_vars[fpc[1]-'0']);
      pc+=strlen(pc)-1;
      fpc+=2;
    }
    else *pc=*fpc;
  }
  *pc=0;
  //printf("\n%s\n",exp);
}

double AvgDouble(char mark,char field,char vars[10][100],long *pn) {
  long at=-1,dat,dlen,n=0;
  char buf[100000],*pc,exp[1000];
  double avg=0.0,d;

  MakeExpLine(exp,vars);
//printf("\n%s\n",exp);
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

double AvgLong(char mark,char field,char vars[10][100],long *pn) {
  long at=-1,dat,dlen,n=0,l;
  char buf[100000],*pc,exp[1000];
  double avg=0.0;
  MakeExpLine(exp,vars);
//printf("\n%s\n",exp);
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


void EatWhite(char *str) {
  char *pc,*pc2,*pc3;
  for (pc=str;*pc==' ';pc++);
  if (pc>str) {
    for (pc2=pc3=str;*pc;pc++,pc2++) {
      *pc2=*pc;
      if (*pc!=' ') pc3=pc2+1;
    }
    *pc3=0;
  }
  else {
    for (pc3=pc;*pc;pc++) if (*pc!=' ') pc3=pc+1;
    *pc3=0;
  }
}

long DoTable(FILE *ifp, char *label, char *caption) {
  char command[MAXCOL][100],*pc,*pc2,buf[1000],under[MAXCOL];
  char varln[1000],comln[1000],prln[1000],*varp,*comp,*prp;
  long ncol=0,col,nc,i,ii,var[MAXCOL],typ,typwas,smcom,n;
  unsigned int len;
  char vars[MAXCOL][10][100];

  printf("\n\\begin{table}[htb]\n");
  printf("\\caption{%s}\n",caption);
  printf("\\label{%s}\n",label);
  printf("\\begin{small}\n");
  printf("\\begin{center}\n");

  for (i=0;i<MAXCOL;i++) {
    command[i][0]=0;
    for(ii=0;ii<10;ii++) *vars[i][ii]=0;
  }


  while (pc=fgetln(ifp,&len)) {
    memcpy(buf,pc,len);
    if (buf[len-1]=='\n') len--;
    buf[len]=0;

    pc=buf;
    if (STRSTARTSWITH(pc,"end table")) break;
    if (STRSTARTSWITH(pc,"exp 0 ")) {strcpy(g_exp[0],pc);continue;}
    if (STRSTARTSWITH(pc,"exp 1 ")) {strcpy(g_exp[1],pc);continue;}
    if (STRSTARTSWITH(pc,"exp 2 ")) {strcpy(g_exp[2],pc);continue;}
    if (STRSTARTSWITH(pc,"exp 3 ")) {strcpy(g_exp[3],pc);continue;}
    if (STRSTARTSWITH(pc,"exp 4 ")) {strcpy(g_exp[4],pc);continue;}
    if (STRSTARTSWITH(pc,"exp 5 ")) {strcpy(g_exp[5],pc);continue;}
    if (STRSTARTSWITH(pc,"var 0 ")) {strcpy(g_vars[0],pc);continue;}
    if (STRSTARTSWITH(pc,"var 1 ")) {strcpy(g_vars[1],pc);continue;}
    if (STRSTARTSWITH(pc,"var 2 ")) {strcpy(g_vars[2],pc);continue;}
    if (STRSTARTSWITH(pc,"var 3 ")) {strcpy(g_vars[3],pc);continue;}
    if (STRSTARTSWITH(pc,"var 4 ")) {strcpy(g_vars[4],pc);continue;}
    if (STRSTARTSWITH(pc,"var 5 ")) {strcpy(g_vars[5],pc);continue;}
    if (STRSTARTSWITH(pc,"var 6 ")) {strcpy(g_vars[6],pc);continue;}
    if (STRSTARTSWITH(pc,"var 7 ")) {strcpy(g_vars[7],pc);continue;}
    if (STRSTARTSWITH(pc,"var 8 ")) {strcpy(g_vars[8],pc);continue;}
    if (STRSTARTSWITH(pc,"var 9 ")) {strcpy(g_vars[9],pc);continue;}

    if (!ncol) {
      pc=strchr(buf,'|');
      if (!pc) {
        fprintf(stderr,"Error: table has no columns\n");
        return(0);
      }
      for (pc=strchr(pc+1,'|');pc;pc=strchr(pc+1,'|'),ncol++) if ((pc[1]>='0')&&(pc[1]<='9')) ncol+=pc[1]-'0'-1;
      if (!ncol) {
        fprintf(stderr,"Error: table has no columns\n");
        return(0);
      }

      printf("\\begin{tabular}{|");
      for (i=0;i<ncol;i++) printf("r|");
      printf("}\n\\hline\n");
    }

    for (i=0;i<ncol;i++) {
      under[i]=0;
    }

    pc=strchr(buf,'|');
    for (col=0;pc&&(col<ncol);col+=nc) {
      if ((pc[1]>='0')&&(pc[1]<='9')) {
        nc=pc[1]-'0';pc++;
        printf("\\multicolumn{%d}{|c|}{",nc);
      }
      else nc=1;
      pc++;
      if (*pc=='_') {
        for (i=0;i<nc;i++) under[col+i]=1;
        pc++;
      }
      for (pc2=strchr(pc,'|');pc2&&(*(pc2-1)=='\\');pc2=strchr(pc2+1,'|'));
      typ=0;
      prp=prln;varp=varln;comp=comln;
      smcom=0;
      for (;pc<pc2;pc++) {
        if ((typwas==0)&&(typ!=0)) {
          *prp=0;
          EatWhite(prln);
          if (*prln) printf(" %s ",prln);
          prp=prln;
        }
        typwas=typ;
        if (*pc=='\\') pc++;
        else {
          if (*pc=='%') {
            if (typ==1) {
              *varp=0;
              if (*varln) {
                varp=varln;
                if ((*varln>='0')&&(*varln<='9')&&((varln[1]=='=')||!varln[1])) {
                  for (i=0;i<nc;i++) var[col+i]=*varln-'0';
                  varp+=varln[1]?2:1;
                }
                if (*varp) for (i=0;i<nc;i++) {
                  strcpy(vars[col+i][var[col+i]],varp);
                  strcpy(g_vars[var[col+i]],varp);
                }
              }
              varp=varln;
              typ=0;
            }
            else typ=1;
            continue;
          }
          else if (*pc=='~') {
            if (typ==2) {
              *comp=0;
              if (smcom) strcpy(comln,command[col]);
              if (*comln) {
                strcpy(command[col],comln);
                comp=comln;
                if ((*comp>='0')&&(*comp<='5')) {g_expInd=*comp-'0';comp++;}
                if (!memcmp(comp,"best",4)) {comp+=4;typ=10;}
                else if (!memcmp(comp,"final",5)) {comp+=5;typ=20;}
                if (!memcmp(comp,"gen",3)) {comp+=3;typ+=1;}
                else if (!memcmp(comp,"time",4)) {comp+=4;typ+=2;}
                else if (!memcmp(comp,"test",4)) {comp+=4;typ+=3;}
                else if (!memcmp(comp,"mse",3)) {comp+=3;typ+=4;}
                n=0;
                switch(typ) {
                case 11: printf(g_pstr,AvgLong('b','b',vars[col],&n));break;
                case 12: printf(g_pstr,AvgDouble('b','t',vars[col],&n));break;
                case 13: printf(g_pstr,100.0*AvgDouble('b','a',vars[col],&n));break;
                case 14: printf(g_pstr2,AvgDouble('b','a',vars[col],&n));break;
                case 21: printf(g_pstr,AvgLong('e','e',vars[col],&n));break;
                case 22: printf(g_pstr,AvgDouble('e','t',vars[col],&n));break;
                case 23: printf(g_pstr,100.0*AvgDouble('e','a',vars[col],&n));break;
                case 24: printf(g_pstr2,AvgDouble('e','a',vars[col],&n));break;
                default: fprintf(stderr,"Error: unknown command in table entry : %s\n",comln);return(0);
                }
                if (*comp=='(') {
                  i=atoi(comp+1);
                  if (i!=n) printf("!!%d matched!!",n);
                }
              }
              comp=comln;
              typ=0;
            }
            else typ=2;
            smcom=1;
            continue;
          }
        }
        switch (typ) {
        case 0: *(prp++)=*pc;break;
        case 1: *(varp++)=*pc;break;
        case 2: *(comp++)=*pc;smcom=0;break;
        }
      }
      *prp=0;
      EatWhite(prln);
      if (*prln) printf(" %s ",prln);

      if (nc>1) printf("}");
      if (col+nc<ncol) printf(" & ");
      else {
        printf(" \\\\ ");
        for (i=ii=0;i<ncol;i++) {
          if ((i>ii)&&!under[i]) printf("\\cline{%d-%d} ",ii+1,i+1);
          if (!under[i]) ii=i+1;
        }
        if (ii==0) printf("\\hline ");
        else if (ii<ncol) printf("\\cline{%d-%d} ",ii+1,ncol);
       if (pc2&&pc2[0]&&(pc2[1]=='_')&&(pc2[2]=='_')) printf("\\hline ");
        printf("\n");
      }
    }
    if (!pc) {fprintf(stderr,"Error: a line in the table has too few columns\n");return(0);}
  }
  printf("\\end{tabular}\n");
  printf("\\end{center}\n");
  printf("\\end{small}\n");
  printf("\\end{table}\n");

  return(1);
}

extern int g_useSem;

int main( int argc, char *argv[] )
{
  FILE *ifp;
  char ifn[200],efn[200],*pc,buf[1000],lab[100];
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

  for (l=0;l<MAXEXP;l++) *g_exp[l]=0;

//  SemWait();
//  g_useSem=0;

  while (pc=fgetln(ifp,&len)) {
    memcpy(buf,pc,len);
    if (buf[len-1]=='\n') len--;
    buf[len]=0;
    pc=buf;
    if (STRSTARTSWITH(pc,"exp 0 ")) strcpy(g_exp[0],pc);
    else if (STRSTARTSWITH(pc,"exp 1 ")) strcpy(g_exp[1],pc);
    else if (STRSTARTSWITH(pc,"exp 2 ")) strcpy(g_exp[2],pc);
    else if (STRSTARTSWITH(pc,"exp 3 ")) strcpy(g_exp[3],pc);
    else if (STRSTARTSWITH(pc,"exp 4 ")) strcpy(g_exp[4],pc);
    else if (STRSTARTSWITH(pc,"exp 5 ")) strcpy(g_exp[5],pc);
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
    else if (STRSTARTSWITH(pc,"table ")) {
      if (sscanf(pc,"%s %n",lab,&len)<1) *lab=0;else pc+=len;
      DoTable(ifp,lab,pc);
    }
    else if (STRSTARTSWITH(pc,"string for print ")) strcpy(g_pstr,pc);
    else if (STRSTARTSWITH(pc,"string2 for print ")) strcpy(g_pstr2,pc);
//    else if (STRSTARTSWITH(pc,"final time")) {printf(pstr,AvgDouble('e','t',&n));tn+=n;}
//    else if (STRSTARTSWITH(pc,"final test acc %")) {printf(pstr,100.0*AvgDouble('e','t',&n));tn+=n;}
//    else if (STRSTARTSWITH(pc,"final gen")) {printf(pstr,AvgLong('e','e',&n));tn+=n;}
//    else if (STRSTARTSWITH(pc,"best val %")) {printf(pstr,100.0*AvgDouble('b','v',&n));tn+=n;}
//    else if (STRSTARTSWITH(pc,"time at best val")) {printf(pstr,AvgDouble('b','t',&n));tn+=n;}
//    else if (STRSTARTSWITH(pc,"test acc at best val %")) {printf(pstr,100.0*AvgDouble('b','a',&n));tn+=n;}
//    else if (STRSTARTSWITH(pc,"gen at best val")) {printf(pstr,AvgLong('b','b',&n));tn+=n;}
  }
  fclose(ifp);

//  g_useSem=1;
//  SemSignal();
}
