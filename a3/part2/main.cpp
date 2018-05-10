/*
Name: David Dobbie

Answer for COMP307 - Introduction to Artifical Intelligence
Assignment 3 - Part 2
Naive Bayes
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

bool DEBUG = false;


/*
@Inputs: file name to be parse
@Function: 
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
      if(DEBUG) printf("%s",line);
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

  int k;

  
  if(argc != 4){
    std::cerr << "You must enter two datasets, the training set and the test set, and a k value\n";
  }
  else{
    trainingFile = *(argv+1);
    parseFile(trainingFile, 1);

    testFile = *(argv+2);
    parseFile(testFile, 0);

    
  }
  std::cout << "Closing...\n";
  return 0;
}



