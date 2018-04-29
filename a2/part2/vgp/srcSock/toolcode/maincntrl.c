// Stream socket client file
// Author : Will Smart   10/04/03



#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "files.h"

struct sockaddr_in name;

char *quitstr="end of evolution";

void DoEvolve(char *buf,char *outbuf,long *oblen) {
  int sock;
  int length;
  char *pc=outbuf;
  // open socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
     perror("opening stream socket");
     exit(1);
  }

  // connect to server
  if ( connect( sock, (struct sockaddr*)&name, sizeof( name ) ) < 0 )
  {
     perror("connecting socket");
     exit(1);
  }

  //printf( "server on port : %d\n", ntohs( name.sin_port ) );

  // send string
  if ( write( sock, buf, strlen(buf) + 1 ) < 0 )
    perror("sending message");

  do {
    if ( ( length = read( sock, pc, (*oblen)-(pc-outbuf)) ) < 0 )
      {perror("receiving");break;}
//    if (length) printf("recieved %d, %d, %s\n",length,(*oblen)-(pc-outbuf),pc);
    pc+=length;
//    if (length) printf("end: %s\n",pc-4);
  } while ((length<strlen(quitstr))||memcmp(pc-strlen(quitstr),quitstr,strlen(quitstr)));

  close(sock);
  *oblen=pc-outbuf-strlen(quitstr);
}

main(int argc, char *argv[])
{
  int sock, i, numloop;
  struct hostent *hp;
  char buf[1024],ob[100000],hstnm[1000],*pc,c=0;
  char *usage="Usage : %s [exp_file_prefix] [host_name:index/Pport]\n";
  long at,dat,oblen;
  int stdinfd,port,ind=0;
  FILE *fil;
  unsigned int len;
  struct timeval timst,timend;

  stdinfd = fcntl(STDIN_FILENO,  F_DUPFD, 0);

  if (argc<3)
  {
     printf( usage, argv[0] );
     exit(1);
  }

  if (!(pc=strchr(argv[2],':'))) {
    strcpy(hstnm,argv[2]);
    ind=1;
  }
  else {
    memcpy(hstnm,argv[2],pc-argv[2]);hstnm[pc-argv[2]]=0;
    if ((pc[1]>='0')&&(pc[1]<='9')) {
      if (!(ind=atoi(pc+1))) {
        printf( "Error: Index should be 1 or more\n" );
        exit(1);
      }
    }
    else if (pc[1]=='P') port=atoi(pc+2);
    else {
      printf( usage, argv[0] );
      exit(1);
    }
  }

  if (ind) {
    if (!(fil=fopen("machines.txt","r"))) {
      printf( "Error: Could not open file \"machines.txt\"\n");
      exit(1);
    }
    while (ind) {
      if (!(pc=fgetln(fil,&len))) break;
      memcpy(buf,pc,len);buf[len]=0;
      if ((!memcmp(hstnm,buf,strlen(hstnm)))&&((buf[strlen(hstnm)]==' ')||(buf[strlen(hstnm)]=='.'))) ind--;
    }
    if (ind) {
      printf( "Error: machines file does not have that many %s entries\n",hstnm);
      exit(1);
    }
    if (sscanf(buf,"%s %d",hstnm,&port)<2) {
      printf( "Error: bad line in machine file (should simply be \"<hstnm> <port>\")\n",hstnm);
      exit(1);
    }
  }

  name.sin_family = AF_INET;
  name.sin_addr.s_addr = INADDR_ANY;
  name.sin_port = htons(port);

  // get server machine from command line
  if ( ( hp = gethostbyname( hstnm ) ) == 0 )
  {
     fprintf( stderr, "%s: unknown host\n", hstnm );
     return(1);
  }
  memcpy( &name.sin_addr, hp->h_addr, hp->h_length );

  if (!InitFiles(argv[1])) {
     fprintf( stderr, "Could not initialize files\n" );
     return(1);
  }

  if ( gettimeofday(&timst, NULL) < 0 ) perror("Getting time");

  while ((at=GetALine('e','+',buf))>=0) {
    oblen=100000;
    if (!(pc=strchr(buf,'>'))) sprintf(buf,"* Bad exp line ");
    else {
      printf("Exp:%s\n",pc+1);
      DoEvolve(pc+1,ob,&oblen);
      dat=AppendDataFile(ob,oblen);
      sprintf(buf,"* %d %d ",dat,oblen);
    }
    MarkLineWith(at,buf);
    ioctl(stdinfd,FIONREAD,&i);
    for (;i;i--) if (getchar()=='q') break;
    if (i) break;
  }
//  DoEvolve("quit:");
  if (at==-1) printf("Error reading file\n");
  else {
    if ( gettimeofday(&timend, NULL) < 0 ) perror("Getting time");
    printf("Experiments %s, took %d sec (%d minutes)\n",(at<0)?"finished":"paused",timend.tv_sec-timst.tv_sec,(timend.tv_sec-timst.tv_sec)/60);
  }
}

