/* File: addplan.c
 Author: Will Smart, 2004

 Description: A program that allows addition of experiments to the experiment file
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

#define INFUNC(val) val
#define STRSTARTSWITH(str,sta) ( ( ( ( *str == ' ' ) && ( str++ ) ) || 1 ) && ( strlen(str) >= strlen(sta) ) && ( !memcmp( str, sta, strlen(sta) ) ) && ( str += strlen(sta) ) )

int minx = 0, miny = 0, maxx = 10000, maxy = 10000, offx, offy;
double scalex, scaley, dminx = 0.0, dminy = 0.0, dmaxx = 100.0, dmaxy = 4.0, x0, y0;

void usage( char *ex ) {
    fprintf( stderr, "Usage : %s [check:period] [new] exp_file_prefix input_file \n", ex );
    exit(1);
}
void err( char *buf, char *pc ) {
    fprintf( stderr, "Error at : %s       point : %s\n", buf, pc );
    exit(3);
}

char params[500][1000];
char varnames[100][1000],vars[100][1000];

int line;
extern int g_useSem;


void UpdateVars(char *loopat) {
    char *pc,*pc2,var[1000];
    int i;
    pc=loopat;
    while(1) {
       for (;*pc&&(*pc!=' ')&&(*pc!='<');pc++);
       if (*pc!='<') break;
       for (pc++,pc2=var;*pc&&(*pc!='>')&&(*pc!='<')&&(*pc!=',');pc++,pc2++) *pc2=*pc;
       *pc2=0;
       if (*pc!=',') {
         fprintf(stderr,"Error, param variable does not have comma seperator, line:%d\n",line);
         exit(0);
       }
       for (i=0;i<100;i++)
         if (!strcmp(varnames[i],var)) break;
       if (i==10) {
         for (i=0;i<10;i++) if (!*varnames[i]) break;
         if (i==100) {
           fprintf(stderr,"Error, no room for var %s\n",var);
           exit(0);
         }
         strcpy(varnames[i],var);
       }
       for (pc++,pc2=var;*pc&&(*pc!='>')&&(*pc!='<');pc++,pc2++) *pc2=*pc;
       *pc2=0;
       if (*pc!='>') {
         fprintf(stderr,"Error, param variable does not have > to end it, line:%d\n",line);
         exit(0);
       }
       strcat(vars[i],var);
    }
}


void AppendParamVal(char *com,char* val) {
    char *pc,*pc2,*pc3,var[1000];
    int i;
    for (pc2=com+strlen(com),pc=val;*pc;pc++,pc2++)
       if (*pc=='<') {
         for (pc3=var,pc++;*pc&&(*pc!='>');pc++,pc3++) *pc3=*pc;
         *pc3=0;
         if (*pc!='>') {
           fprintf(stderr,"Error, inline variable does not have > to end it, line:%d\n",line);
           exit(0);
         }
         for (i=0;i<100;i++) if (!strcmp(varnames[i],var)) break;
         if (i==100) {
           fprintf(stderr,"Error, inline variable does not exist : %s, line:%d\n",var,line);
           exit(0);
         }
         strcpy(pc2,vars[i]);
         pc2+=strlen(pc2)-1;
       }
       else *pc2=(*pc=='~')?' ':*pc;
    *pc2=0;
}


char FindNext(char *loopname,char *loopat, char *loopval) {
    int i=0;
    char ret=1,*pc,*pc2;
    if (*loopat) {
       while (params[i][0]&&strcmp(params[i],loopat)) i++;
       if (!params[i][0]) {
         fprintf(stderr,"Error, could not find loopat param %s, line:%d\n",loopat,line);
         exit(0);
       }
       i++;
    }
    while (params[i][0]&&memcmp(params[i],loopname,strlen(loopname))) i++;
    if (!params[i][0]) {
       i=0;
       ret=0;
       while (params[i][0]&&memcmp(params[i],loopname,strlen(loopname))) i++;
       if (!params[i][0]) {
         fprintf(stderr,"Error, could not find loopname param %s, line:%d\n",loopname,line);
         exit(0);
       }
    }
    strcpy(loopat,params[i]);
    for (pc=params[i];*pc&&(*pc!=' ');pc++);
    if (!*pc) {
       pc=params[i];
       for (pc2=loopval;*pc&&(*pc!='<');pc++,pc2++) *pc2=*pc;
    }
    else {
      while(*pc==' ') pc++;
      for (pc2=loopval;*pc;pc++,pc2++) *pc2=*pc;
    }
    *pc2=0;
    return(ret);
}


int main( int argc, char *argv[] )
{
    FILE *ifp;
    int argn, cnt, ni, i, ii, iii, ocnt, numchar, skp,num[100],at,numloop,numinner=1,numlns=0,nwfil=0;
    double dx,dy,ddx,ddy,tot[100];
    char ifn[100], efn[100], buf[1000], lbuf[1000], obuf[10000],obufs[1000],obufe[1000], *pc, *pc2, *stln, c;
    char loopname[100][1000],loopat[100][1000],loopval[100][1000];
    char outp[1000],outpeach[1000],outpstrt[1000],outpend[1000];
    unsigned int len;
    long chk=0,cat,cfail;
    argn = 1;
//    if ( argn == argc)
//       usage( argv[0] );

//    if (sscanf(argv[argn], "%d", &offset) != 1)
//       usage( argv[0] );

//    argn++;
    if ( argn == argc) usage( argv[0] );

    if (!memcmp(argv[argn],"check:",6)) {
      chk=atoi(argv[argn]+6);
      argn++;
      if ( argn == argc) usage( argv[0] );
    }

    strcpy(efn,argv[argn]);

    if (!strcmp(efn,"new")) {
      argn++;
      if ( argn == argc) usage( argv[0] );
      strcpy(efn,argv[argn]);
      nwfil=1;
      MakeNewFiles(efn);
    }
    argn++;
    if ( argn == argc) usage( argv[0] );
    strcpy(ifn,argv[argn]);

    argn++;
    if ( argn != argc) usage( argv[0] );

    if ( (ifp = fopen(ifn, "r")) == NULL ) {
      fprintf( stderr, "Could not open file %s\n", ifn );
      exit(2);
    }

    if (!InitFiles(efn)) {
       fprintf( stderr, "Could not initialize files\n" );
       return(1);
    }
    SemWait();
    g_useSem=0;

    at=0;
    line=0;
    while ((pc = fgetln( ifp, &len ))) {
       for (i=0;*pc&&(*pc!='\n');pc++,i++) buf[i]=*pc;
       buf[i]=0;
       pc=buf;
       if (*pc!='#') continue;
       pc++;
       if (*pc=='~') strcpy(params[at++],pc+1);
       continue;
    }
    fseek(ifp,0,SEEK_SET);
    line=0;
    while ((pc = fgetln( ifp, &len ))) {
       line++;
       for (i=0;*pc&&(*pc!='\n');pc++,i++) buf[i]=*pc;
       buf[i]=0;
       pc=buf;
       if ((*pc!='#')||(pc[1]!='#')) continue;
       pc+=2;

       i=0;
       *outp=0;
       numinner=-1;
       while ((*pc)&&(*pc!='\n')) {
         if (*pc=='>') {
           for (pc=pc+1;*pc==' ';pc++);
           strcpy(outp,pc);
           break;
         }
         if (*pc=='|') {
           numinner=0;
           if (*++pc==' ') {
             while(*pc==' ') pc++;
             continue;
           }
         }
         for (pc2=loopname[i++];*pc&&(*pc!=' ')&&(*pc!='\n');pc++,pc2++) *pc2=*pc;
         *pc2=0;
         if (numinner>=0) numinner++;
         while(*pc==' ') pc++;
       }
       loopname[i][0]=0;
       numloop=i;
       if (numinner<0) numinner=1;

       for (i=0;i<100;i++) {
         loopat[i][0]=0;
         if (i<numloop-1) FindNext(loopname[i],loopat[i],loopval[i]);
         varnames[i][0]=0;
       }
       *obuf=0;
       for (pc=outp;*pc&&(*pc!='{');pc++);
       if (!*pc) {
         *outpeach=0;
         strcpy(outpstrt,outp);
         *outpend=0;
       }
       else {
         memcpy(outpstrt,outp,pc-outp);
         outpstrt[pc-outp]=0;
         for (pc++,pc2=outpeach;*pc&&(*pc!='}');pc++,pc2++) *pc2=*pc;
         *pc2=0;
         if (!*pc) {
           fprintf(stderr,"Error, no } on output part, line:%d\n",line);
           exit(0);
         }
         strcpy(outpend,pc+1);
       }
       ocnt=0;
       while(1) {
         for (i=numloop-1;i>=0;i--)
           if (FindNext(loopname[i],loopat[i],loopval[i])) break;
         for (ii=0;ii<100;ii++) {
           varnames[ii][0]=0;
           vars[ii][0]=0;
         }
         for (ii=0;ii<numloop;ii++)
           UpdateVars(loopat[ii]);
         if (i<numloop-numinner) {
           if (ocnt) {
             *buf=0;
             //printf("#%s%s%s\n",obufs,obuf,obufe);
             *obuf=0;
             ocnt=0;
           }
         }
         if (i<0) break;
         else {
           if (!ocnt) {
             *obufs=*obufe=*obuf=0;
             AppendParamVal(obufs,outpstrt);
             AppendParamVal(obufe,outpend);
           }
           ocnt++;
           if (*outpeach) {
             AppendParamVal(obuf,outpeach);
             strcat(obuf," ");
           }
         }
       }
    }
    fseek(ifp,0,SEEK_SET);
    line=0;
    while ((pc = fgetln( ifp, &len ))) {
       line++;
       for (i=0;*pc&&(*pc!='\n');pc++,i++) buf[i]=*pc;
       buf[i]=0;
       pc=buf;
       if ((*pc!='#')||(pc[1]!='#')) continue;
       pc+=2;

       i=0;
       *outp=0;
       while ((*pc)&&(*pc!='\n')) {
         if (*pc=='>') {
           for (pc=pc+1;*pc==' ';pc++);
           strcpy(outp,pc);
           break;
         }
         if (*pc=='|') {
           if (*++pc==' ') {
             while(*pc==' ') pc++;
             continue;
           }
         }
         for (pc2=loopname[i++];*pc&&(*pc!=' ')&&(*pc!='\n');pc++,pc2++) *pc2=*pc;
         *pc2=0;
         while(*pc==' ') pc++;
       }
       loopname[i][0]=0;
       numloop=i;

       for (i=0;i<100;i++) {
         loopat[i][0]=0;
         if (i<numloop-1) FindNext(loopname[i],loopat[i],loopval[i]);
         varnames[i][0]=0;
       }
       *obuf=0;
       cat=0;cfail=0;
       while(1) {
         for (i=numloop-1;i>=0;i--)
           if (FindNext(loopname[i],loopat[i],loopval[i])) break;
         for (ii=0;ii<100;ii++) {
           varnames[ii][0]=0;
           vars[ii][0]=0;
         }
         for (ii=0;ii<numloop;ii++)
           UpdateVars(loopat[ii]);
         if (i<0) break;
         for (*buf=0,i=0;i<numloop;i++) {
           AppendParamVal(buf,loopval[i]);
           if (i<numloop-1) strcat(buf," ");
         }
         sprintf(lbuf,"e                        >%s\n",buf);
//	 printf("%s\n",buf);
         if (!(ii=(chk&&(cfail||!(cat%chk)))?AppendLineIfNew(lbuf,buf):AppendLine(lbuf))) {
           fprintf(stderr,"Failed to append: %s",buf);
           exit(0);
         }
         else if (ii==-1) {
           cfail=1;
         } //printf("Line exists: %s",buf);
         else {
           cfail=0;
           if (!((++numlns)%10)) fprintf(stderr,".");
         }
         cat++;
       }
    }
    fclose(ifp);

    g_useSem=1;
    SemSignal();

    printf("\n%d experiments added\n",numlns);
}

