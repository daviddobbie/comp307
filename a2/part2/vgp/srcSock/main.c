/* File: main.c
 Author: Will Smart, 2004

 Description: the main procedure, that initializes and loops for evolution, also parses args
          In order to specialize the procedures here, write a new file with whichever procedures to be rewritten
            Then define the appropriate compiler define to mask out the old procedure, and #include3 this file
            See the examples (eg Classify) for an example specialization
*/

#define Headers

#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../src/common.h"
#include "../src/node.h"
#include "../src/op.h"
#include "../src/allc.h"
#include "../src/pop.h"
#include "../src/fit.h"
#include "../src/rand.h"

extern long maxnodes;
extern NodeStore ns;


void DoEvolve(void);



long ParseArgs(int argc, char *argv[]);

int sock, g_consock, quit=0;
unsigned int length;
struct sockaddr_in name, conname;
struct hostent *hp, *gethostbyname();

char *quitstr="end of evolution";

void InitSocket(void) {
  FILE *fil;
  char buf[1000],buf2[1000];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
     perror("opening stream socket");
     exit(1);
  }

  name.sin_family = AF_INET;
  name.sin_addr.s_addr = INADDR_ANY;
  name.sin_port = 0;
  if (bind(sock, (struct sockaddr*)&name, sizeof(name)))
  {
     perror("binding stream socket");
     exit(1);
  }

  length = sizeof(name);
  if (getsockname(sock, (struct sockaddr*)&name, &length))
  {
      perror("getting socket name");
      exit(1);
  }

  printf( "Socket bound to port %d\n", ntohs( name.sin_port ) );

  if (!(fil=fopen("../srcSock/machines.txt","a"))) printf("Could not open machine file.\n");
  else {
    gethostname(buf,1000);
    sprintf(buf2,"%s %d\n",buf,ntohs( name.sin_port ));
    fwrite(buf2,1,strlen(buf2),fil);
    fclose(fil);
  }

  if ( listen( sock, 1 ) )
  {
      perror("listening");
      exit(1);
  }
}

int GetInstructions(void) {
  char buf[1024],*av[100],nm[10]="vgp",*pc;
  int ac,i,len;
  length = sizeof( conname );
  // new connection
  if ( ( g_consock = accept( sock, (struct sockaddr*)&conname, &length ) ) == -1 )
  {
    perror("accepting connection");
    exit(1);
  }
  *buf=0;

  do {
    // get call from client
    if ( ( len = read( g_consock, buf, 1024) ) < 0 )
      perror("receiving");
    else if (len)
    {
      if (strstr(buf,"quit:")) quit=1;
      else {
        av[0]=av[1]=buf;ac=1;
        while (av[ac]) {
          av[ac+1]=pc=strchr(av[ac],' ');
          ac++;
          if (av[ac]) {
            while (*av[ac]==' ') av[ac]++;
            *pc=0;
          }
        }
        if (!ParseArgs(ac,av)) return(0);
        if (POUT(2)) {
          printf("Args OK : ");
          for ( i = 0; i < ac; i++ ) printf("%s ",av[i]);
            printf("\n");
        }
      }
      return(1);
    }
  } while (length);
}

void CloseConnection(void) {
  close( g_consock );
}

void CloseMainConnection(void) {
  close( sock );
}
//************************************************************************* Function: main
// Args:          Command line
// Description: The main procedure for the program,
// Waits on a socket for instructions, and performs evolutions as neccesary
#define Dmain
int main(int argc, char *argv[]) {
  long gen,npats,i,bstgen;
  long nel,nmut,troff,trnum,vaoff,vanum,teoff,tenum;
  Fit best,bstva,vafit,tefit;
  Pop *fpop,*tpop,pop1,pop2,*tempPop;
  Pat *pats=NULL;
  char buf[10000];
  clock_t tim,tim2,timv;

  g_fullRate=0.5;
  g_maxDepth=6;
  g_minDepth=3;

  if (!ParseArgs(argc,argv)) exit(0);

  if (POUT(3)) {
   printf("Args OK : ");
   for ( i = 0; i < argc; i++ ) printf("%s ",argv[i]);
   printf("\n");
  }

  if (POUT(4)) printf("Initializing nodespace with %d nodes ..\n",maxnodes);
  if (!InitNodeStore(maxnodes)) {
    if (PERR) printf("Couldn't allocate nodespace\n");
    return(1);
  }

  InitOps();



  InitSocket();
  while (1) {
    if (!GetInstructions()) {
      if ( write( g_consock, "\"!!!bad args\"",13 ) < 0 ) perror("sending message");
    }
    else if (g_verbose==-1) {
      if ( write( g_consock, "\"OK\"",4 ) < 0 ) perror("sending message");
    }
    else {
      if (quit) break;
  if (POUT(1)) {
    printf("At start of evolution : NodeIndex: %d, Allocated: %d\n",ns.freeIndex,g_totMalloc);
  }
      DoEvolve();
    }
    if ( write( g_consock, quitstr,strlen(quitstr) ) < 0 ) perror("sending message");
    if (POUT(4)) printf("Sent EOE\n\n");
    CloseConnection();
  }
  if (POUT(4)) printf("Got quit message, quitting.\n");
  CloseMainConnection();

}
