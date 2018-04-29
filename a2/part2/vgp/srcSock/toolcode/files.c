#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int g_sem=-1;
char g_fn[200]="";
char g_dfn[200]="";
long g_at=0;
int g_useSem=1;
FILE *g_fil=NULL,*g_dfil=NULL;

int SemSignal(void) {
  struct sembuf op;
  if (!g_useSem) return(1);
  op.sem_num=0;
  op.sem_op=1;
  op.sem_flg=0;
  if ((g_sem==-1)||(semop(g_sem,&op,1)==-1)) return(0);
  return(1);
}

int SemWait(void) {
  struct sembuf op;
  if (!g_useSem) return(1);
  op.sem_num=0;
  op.sem_op=-1;
  op.sem_flg=0;
  if ((semop(g_sem,&op,1)==-1)) return(0);
  return(1);
}

int ResetSem(char *fnprfx) {
  key_t key;
  char fn[200];
  int v=1;
  sprintf(fn,"%s.txt",fnprfx);
  if ((key=ftok(fn,'a'))==(key_t)-1) return(0);
  printf("key:%d\n",key);
  if ((g_sem = semget(key, 0, 0)) == -1) {
    printf("Semaphore does not exist\n");return(0);
  }
  if (semctl(g_sem, 0, SETVAL, v) == -1) {
    printf("Semaphore could not be reset\n");return(0);
  }
  else printf("Semaphore reset\n");
  return(1);
}

int InitSem(void) {
  struct sembuf op;
  key_t key;
  if ((key=ftok(g_fn,'a'))==(key_t)-1) return(0);
  if ((g_sem = semget(key, 0, 0)) == -1) {
    printf("Semaphore does not exist, creating it\n");
    if ((g_sem = semget(key, 1, IPC_CREAT | IPC_EXCL | S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) != -1)
    {
        op.sem_num = 0;
        op.sem_op = 2;  /* This is the number of runs without queuing. */
        op.sem_flg = 0;
        if (semop(g_sem, &op, 1) == -1) {
            perror("IPC error: semop"); return(0);
        }
    }
    else if (errno == EEXIST) {
        if ((g_sem = semget(key, 0, 0)) == -1) {
            perror("IPC error 1: semget"); return(0);
        }
    }
    else {
        perror("IPC error 2: semget"); return(0);
    }
  }
  return(1);
}

int InitFiles(char *fnprfx) {
  char fn[200],dfn[200];
  FILE *fil;
  sprintf(fn,"%s.txt",fnprfx);
  sprintf(dfn,"%s.b",fnprfx);
  strcpy(g_fn,fn);
  strcpy(g_dfn,dfn);
  if (!InitSem()) {
    fprintf(stderr,"Could not initialize semaphore for file access. Does file %s exist?\n",g_fn);
    return(0);
  }
  //SemSignal();
  if (!SemWait()) {
    fprintf(stderr,"Could not wait on file access semaphore\n");
    return(0);
  }
  if (!(fil=fopen(g_fn,"r+"))) {
    fprintf(stderr,"Could not open experiment file %s\n",g_fn);
    return(0);
  }
  fclose(fil);
  if (!(fil=fopen(g_dfn,"r+"))) {
    fprintf(stderr,"Could not open data file %s\n",g_dfn);
    return(0);
  }
  fclose(fil);
  if (!SemSignal()) {
    fprintf(stderr,"Could not signal file access semaphore\n");
    return(0);
  }
  return(1);
}


int MakeNewFiles(char *fnprfx) {
  char fn[200],dfn[200];
  FILE *fil;
  sprintf(fn,"%s.txt",fnprfx);
  sprintf(dfn,"%s.b",fnprfx);
  strcpy(g_fn,fn);
  strcpy(g_dfn,dfn);
  if (!(fil=fopen(g_fn,"w"))) {
    fprintf(stderr,"Could not truncate (or create) experiment file %s\n",g_fn);
    return(0);
  }
  fclose(fil);
  if (!(fil=fopen(g_dfn,"w"))) {
    fprintf(stderr,"Could not truncate (or create) data file %s\n",g_dfn);
    return(0);
  }
  fclose(fil);
  return(1);
}


long GetALine(char frommark,char tomark,char *linebuf) {
  FILE *fil;
  long ret=-1;
  unsigned int len;
  int ni;
  char *pc;
  if (!SemWait()) return(-1);
  do {
    if (!(fil=fopen(g_fn,"r+"))) break;
    if (fseek(fil,g_at,SEEK_SET)==-1) break;
    ni=0;
    do {
      if (!(pc=fgetln(fil,&len))) {
        if (feof(fil)) {
          if (ni++) break;
          g_at=0;
          if (fseek(fil,g_at,SEEK_SET)==-1) break;
          continue;
        }
        else break;
      }
      if (*pc==frommark) break;
      g_at+=len;
    } while(1);
    if (!pc) break;
    memcpy(linebuf,pc,len);
    if (linebuf[len-1]=='\n') len--;
    linebuf[len]=0;
    if (fseek(fil,g_at,SEEK_SET)==-1) break;
    if (fwrite(&tomark,1,1,fil)<1) break;
    ret=g_at;
    g_at+=len;
    if (fseek(fil,g_at,SEEK_SET)==-1) g_at=0;
  } while(0);
  if (fil) fclose(fil);
  if (!SemSignal()) return(-1);
  if (ret==-1) return((ni==2)?-2:-1);
  return(ret);
}

int MarkLineWith(long at,char *tomark) {
  FILE *fil;
  int ret=0;
  int len,ni;
  char *pc;
  if (!SemWait()) return(0);
  do {
    if (!(fil=fopen(g_fn,"r+"))) break;
    if (fseek(fil,at,SEEK_SET)==-1) break;
    if (fwrite(tomark,1,strlen(tomark),fil)<strlen(tomark)) break;
    ret=1;
  } while(0);
  if (fil) fclose(fil);
  if (!SemSignal()) return(0);
  return(ret);
}

int LineSame(char *s1,char *s2) {
  char *pc1=s1,*pc2=s2,*pc;
  int len1,len2,num1=0,num2=0;
  for (pc2=s2;pc2&&*pc2;pc2=strchr(pc2,' '),pc2=pc2?pc2+1:NULL) num2++;
  for (pc1=s1;pc1&&*pc1;pc1=strchr(pc1,' '),pc1=pc1?pc1+1:NULL,num1++) {
    pc=strchr(pc1,' ');
    len1=pc?pc-pc1:strlen(pc1);
    if (!len1) continue;
    if (pc1[len1-1]=='\n') len1--;
    if (!len1) continue;
    for (pc2=s2;pc2&&*pc2;pc2=strchr(pc2,' '),pc2=pc2?pc2+1:NULL) {
      pc=strchr(pc2,' ');
      len2=pc?pc-pc2:strlen(pc2);
      if (!len2) continue;
      if (pc2[len2-1]=='\n') len2--;
      if (!len2) continue;
      if (pc1[len1-1]!='~') {
        if (pc2[len2-1]!='~') {
          if ((len1==len2)&&!memcmp(pc1,pc2,len1)) break;
        }
        else {
          if ((len1>=len2-1)&&!memcmp(pc1,pc2,len2-1)) break;
        }
      }
      else {
        if (pc2[len2-1]!='~') {
          if ((len2>=len1-1)&&!memcmp(pc1,pc2,len1-1)) break;
        }
        else {
          if ((len1==len2)&&!memcmp(pc1,pc2,len1)) break;
        }
      }
    }
    if (!(pc2&&*pc2)) break;
  }
  if ((num1==num2)&&!(pc1&&*pc1)) return(1);
  return(0);
}

long FindNextMatchingLine(long at,char *match,char *buf) {
  FILE *fil;
  long ret=-1,n=0;
  unsigned int len;
  char *pc,lbuf[1000];
  if (!SemWait()) return(-1);
  do {
    if (!g_useSem) {
      if ((!g_fil)&&(!(g_fil=fopen(g_fn,"r+")))) break;
      fil=g_fil;
    }
    else if (!(fil=fopen(g_fn,"r+"))) break;
    if (fseek(fil,(at==-1)?0:at,SEEK_SET)==-1) break;
    if (at==-1) n=1;
    do {
      at=ftell(fil);
      if (!(pc=fgetln(fil,&len))) break;
      if (n++) {
        memcpy(lbuf,pc,len);lbuf[len]=0;
        if ((pc=strchr(lbuf,'>'))&&LineSame(pc+1,match)) break;
      }
    } while(1);
    if (pc) {
      strcpy(buf,lbuf);
      ret=at;
    }
  } while(0);
  if (g_useSem&&fil) fclose(fil);
  if (!SemSignal()) return(-1);
  return(ret);
}

int AppendLine(char *buf) {
  FILE *fil;
  long ret=0;
  int len,ni;
  char *pc;
  if (!SemWait()) return(0);
  do {
    if (!g_useSem) {
      if ((!g_fil)&&(!(g_fil=fopen(g_fn,"r+")))) break;
      fil=g_fil;
    }
    else if (!(fil=fopen(g_fn,"r+"))) break;
    if (fseek(fil,0,SEEK_END)==-1) break;
    if (fwrite(buf,1,strlen(buf),fil)<strlen(buf)) break;
    ret=1;
  } while(0);
  if (g_useSem&&fil) fclose(fil);
  if (!SemSignal()) return(0);
  return(ret);
}

int AppendLineIfNew(char *buf,char *substr) {
  FILE *fil;
  long ret=0;
  unsigned int len;
  char *pc,lbuf[1000];
  if (!SemWait()) return(0);
  do {
    if (!g_useSem) {
      if ((!g_fil)&&(!(g_fil=fopen(g_fn,"r+")))) break;
      fil=g_fil;
    }
    else if (!(fil=fopen(g_fn,"r+"))) break;
    if (fseek(fil,0,SEEK_SET)==-1) break;
    do {
      if (!(pc=fgetln(fil,&len))) break;
      memcpy(lbuf,pc,len);lbuf[len]=0;
      if ((pc=strchr(lbuf,'>'))&&LineSame(pc+1,substr)) break;
    } while(1);
    if (!pc) {
      if (!feof(fil)) break;
      if (fseek(fil,0,SEEK_END)==-1) break;
      if (fwrite(buf,1,strlen(buf),fil)<strlen(buf)) break;
      fflush(fil);
      ret=1;
    }
    else ret=-1;
  } while(0);
  if (g_useSem&&fil) fclose(fil);
  if (!SemSignal()) return(0);
  return(ret);
}

long AppendDataFile(char *buf,long buflen) {
  FILE *fil;
  long ret=0,at;
  int len,ni;
  char *pc;
  if (!SemWait()) return(0);
  do {
    if (!(fil=fopen(g_dfn,"r+"))) break;
    if (fseek(fil,0,SEEK_END)==-1) break;
    at=ftell(fil);
    if (fwrite(buf,1,buflen,fil)<buflen) break;
    ret=at;
  } while(0);
  if (fil) fclose(fil);
  if (!SemSignal()) return(0);
  return(ret);
}

int ReadDataFile(long at,long len,char *buf) {
  FILE *fil;
  long ret=0;
  char *pc;
  if (!SemWait()) return(0);
  do {
    if (!g_useSem) {
      if ((!g_dfil)&&(!(g_dfil=fopen(g_dfn,"r+")))) break;
      fil=g_dfil;
    }
    else if (!(fil=fopen(g_dfn,"r+"))) break;
    if (fseek(fil,at,SEEK_SET)==-1) break;
    if (fread(buf,1,len,fil)<len) break;
    ret=1;
  } while(0);
  if (g_useSem&&fil) fclose(fil);
  if (!SemSignal()) return(0);
  return(ret);
}

