
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


long RemoveExp(char *exp) {
  long at=-1,n=0;
  char buf[1000];
  while ((at=FindNextMatchingLine(at,exp,buf))!=-1) {
    MarkLineWith(at,"e");
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

  printf("Removing: %s\n",exp);
  n=RemoveExp(exp);

  printf("Removed %d experiments\n",n);
  return(0);
}
