/*
Name: David Dobbie

Answer for COMP307 - Introduction to Artifical Intelligence
Assignment 2 - Part 2
Genetic Programming Symbolic Regression
*/


using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vgp\src\allc.h"
#include "vgp\src\common.h"
#include "vgp\src\fit.h"
#include "vgp\src\node.h"
#include "vgp\src\op.h"
#include "vgp\src\pop.h"
#include "vgp\src\rand.h"

bool DEBUG = false;


/*
@Inputs: file name to be parse
@Function: parses the data provided in the file into the format required
            to apply the ML technqiue
*/
 void parseFile(char* fileName, int isTraining){
  char* localName = fileName;

  char line[256];

  int iterId=0;



  std::cout << "Parsing..."<< localName<< "\n";

  FILE * inFile;
  inFile = fopen(localName, "r");

  if(!inFile){

    std::cout << "Opening file failed\n";
    return;
  }

  // parse thru each line, returns it as a string
  while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
  }

  fclose(inFile);
  std::cout << "Parsing "<< localName<< " Complete \n";
  return;

}

/*
@Inputs: command arguments: the dataset to be parse and read from
@Function: to initialise the datasets in the program to be processed
*/
int main(int argc, char** argv)
{
  char * trainingFile;
  char * testFile;



  // initialise the population set
  Pop * pop;
  long num = 10.0;
  InitPop(pop,num);

  if(argc != 4){
    std::cerr << "You must enter two datasets, the training set and the test set, and a k value\n";
  }
  else{
    trainingFile = *(argv+1);
    parseFile(trainingFile, 1);

    testFile = *(argv+2);
    parseFile(testFile, 0);


    parseFile(testFile, 1);
  }
  std::cout << "Closing...\n";
  return 0;
} 


