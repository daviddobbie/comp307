
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

#define STRSTARTSWITH(str,sta) ( ( ( ( *str == ' ' ) && ( str++ ) ) || 1 ) && ( strlen(str) >= strlen(sta) ) && ( !memcmp( str, sta, strlen(sta) ) ) && ( str += strlen(sta) ) )

#define MAXEXP 6
#define MAXCOL 20


void DisplayExp(char *ebuf) {
  long dat,dlen,l;
  char buf[100000],*pc;
  double d;

  do {
    if (*ebuf!='*') break;
    pc=strchr(ebuf,'>');
    if (pc) printf("Exp: %s  ",pc+1);else break;
    if (sscanf(ebuf+2,"%d %d",&dat,&dlen)<2) {printf("Could not get offset/length\n");break;}
    if (!ReadDataFile(dat,dlen,buf)) {printf("Could not get block for data\n");break;}
    for (pc=buf;(pc-buf<dlen)&&*pc;) {
      if (((*pc>='a')&&(*pc<='z'))||((*pc>='A')&&(*pc<='Z'))) {
        printf("<%c>:",*pc);
        pc++;
      }
      else if (*pc=='"') {
        printf("\n");
        for (pc++;pc-buf<dlen;pc++) if (*pc=='"') break;else printf("%c",*pc);
        if (*pc=='"') {pc++;printf("\n");}
        else printf("!!NOT TERMINATED\n");
      }
      else {
        if (*pc==sizeof(double)) {
          d=*(double*)(pc+1);
          printf("(%.5f)",d);
        }
        else if (*pc==sizeof(long)) {
          l=*(long*)(pc+1);
          printf("(%d)",l);
        }
        else printf("Unknown type\n");
        pc+=*pc+1;
      }
    }
  } while(0);
}

long DisplayExps(char *exp) {
  long at=-1,n=0;
  char buf[1000];
  while ((at=FindNextMatchingLine(at,exp,buf))!=-1) {
    DisplayExp(buf);
    n++;
  }
  return(n);
}

void usage( char *ex ) {
    fprintf( stderr, "Usage : %s exp_file_prefix exp_string \n", ex );
    exit(1);
}
void err( char *buf, char *pc ) {
    fprintf( stderr, "Error at : %s       point : %s\n", buf, pc );
    exit(3);
}

extern int g_useSem;

int main( int argc, char *argv[] )
{
  char exp[1000],efn[200];
  long n=0;

  if ( argc != 3)
    usage( argv[0] );

  strcpy(efn,argv[1]);
  strcpy(exp,argv[2]);

  if (!InitFiles(efn)) {
    fprintf( stderr, "Could not initialize files\n" );
    return(1);
  }

  printf("Finding: %s\n",exp);
  n=DisplayExps(exp);

  printf("Found %d experiments\n",n);
  return(0);
}
