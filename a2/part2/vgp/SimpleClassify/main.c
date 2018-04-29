/* File: main.c
 Author: Will Smart, 2004

 Description: Specialization of arg parsing procedure
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../src/node.h"
#include "../src/op.h"
#include "../src/allc.h"
#include "../src/pop.h"
#include "../src/fit.h"
#include "../src/rand.h"

#define Headers

extern char g_setstr[100];

#define STRSTARTSWITH(str,sta) ( ( strlen(str) >= strlen(sta) ) && !memcmp( str, sta, strlen(sta) ) )

#define DParseArg
long BaseParseArg(char *arg);
long ParseArg(char *arg) {
  if (STRSTARTSWITH(arg, "sets:")) strcpy(g_setstr,arg + 5);
  else if (!BaseParseArg(arg)) return(0);
  return(1);
}

#define DHelpScreen
void BaseHelpScreen();
void HelpScreen() {
  BaseHelpScreen();
  if (POUT(1)) fprintf(stderr,"    sets:<str>         layout of sets in pattern file (default : rvs)\n");
}


// include the base procedures (except masked out ones)
#ifndef NOINCLUDEBASE
#include "../src/main.c"
#endif
