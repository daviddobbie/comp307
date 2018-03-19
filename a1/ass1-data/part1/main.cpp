/*
Name: David Dobbie

Answer for COMP307 - Introduction to Artifical Intelligence
Assignment 1 - Part 1
Nearest Neighbour Method
*/
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
  int id;
  double sepalLength;
  double sepalWidth;
  double petalLength;
  double petalWidth;
  char* type;
}plant;

//vector<plant>  trainedPlants;

//vector<plant>  testPlants;


/*
@Inputs: file name to be parse
@Function: parses the data provided in the file into the format required
            to apply the ML technqiue
*/
int parseFile(char* fileName, int isTraining){
  char* localName = fileName;

  char line[256];

  int iterId=0;


  std::cout << "Parsing..."<< localName<< "\n";

  FILE * inFile;
  inFile = fopen(localName, "r");

  if(!inFile){

    std::cout << "Opening file failed\n";
    return 0;
  }





  // parse thru each line, returns it as a string
  while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
      printf("%s",line);
      char * ptr;

      plant p;
      p.id = iterId;    

      //extracts out the doubles number by number.
      p.sepalLength = strtod(line, &ptr);
      p.sepalWidth = strtod(ptr, &ptr);    
      p.petalLength = strtod(ptr, &ptr); 
      p.petalWidth = strtod(ptr, &ptr);
      strcpy(p.type, ptr);

      //diagnostic print out of data stored
      printf("%d, %lf %lf %lf %lf %s\n", p.id, p.sepalLength, p.sepalWidth, p.petalLength, p.petalWidth, p.type);

      iterId ++;
      //if(isTraining)trainedPlants.push_back(p);
      //else testPlants.push_back(p);
  }

  fclose(inFile);

  return 0;

}

/*
@Inputs: command arguments: the dataset to be parse and read from
@Function: to initialise the datasets in the program to be processed
*/
int main(int argc, char** argv)
{
  char * trainingFile;
  char * testFile;

  if(argc != 3){
    std::cerr << "You must enter two datasets, the training set and the test set\n";
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



