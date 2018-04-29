#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc,char *argv[]) {
  key_t key;
  unsigned int sem;
  char fn[256];
  if (argc<2) {
    printf("Usage: removesem k<key>/i<id>/<db_prefix>\n");
    return(0);
  }
  if (*argv[1]=='k') {
    key=atoi(argv[1]+1);
    printf("Removing semaphore with key %d..\n",key);
    if ((sem = semget(key, 0, 0)) == -1) {
      printf("Semaphore does not exist\n");return(0);
    }
  }
  else if (*argv[1]=='i') {
    sem=atoi(argv[1]+1);
    printf("Removing semaphore with id %d..\n",sem);
  }
  else {
    sprintf(fn,"%s.txt",argv[1]);
    if ((key=ftok(fn,'a'))==(key_t)-1) {
      printf("Failed to make key, does file (%s) exist?\n",fn);
      return(0);
    }
    if ((sem = semget(key, 0, 0)) == -1) {
      printf("Semaphore does not exist\n");return(0);
    }
  }
  if (semctl(sem, 0, IPC_RMID, 0) == -1) {
    printf("Semaphore could not be removed\n");return(0);
  }
  printf("Semaphore removed\n");
  return(0);
}

