#include <stdio.h>
#include "files.h"


int main(int argc,char *argv[]) {
  if (argc<2) printf("Usage : %s exp_file_prefix",argv[0]);
  ResetSem(argv[1]);
}

