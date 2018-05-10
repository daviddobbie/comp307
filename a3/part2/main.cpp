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

bool DEBUG = true;

typedef struct{
  vector<int> attributes;
  int result;
} dataRow;

vector<dataRow> trainingData;
vector<dataRow> testData;

/*
@Inputs: file name to be parse
@Function: poarses the file and returns a table of data
*/
vector<dataRow> parseFile(char* fileName, int isTraining){
  char* localName = fileName;

  char line[256];

  int iterId=0;

  vector<dataRow> tableData;

  std::cout << "Parsing..."<< localName<< "\n";

  FILE * inFile;
  inFile = fopen(localName, "r");

  if(!inFile){

    std::cout << "Opening file failed\n";
    return tableData;
  }

  // parse thru each line, returns it as a string
  while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
      if(DEBUG) printf("%s",line);
      dataRow d;
      char * ptr = line;
      int count = 0;
      while (*ptr != '\0')
      {   
          //if(DEBUG) printf("%c\n",*ptr);
          if(*ptr != ' ')
          {
            if (count < 12){
                d.attributes.push_back((int)*ptr - '0');
                count ++;
            } 
            else{
              if(isTraining == 1) d.result = (int)*ptr - '0';
              else d.result = 0; // default to classify as not spam for the test set
              break; // reached the end
            }
          }
          ptr ++;
      }
      tableData.push_back(d);

  }

  fclose(inFile);
  std::cout << "Parsing "<< localName<< " Complete \n";
  return tableData;

}

/*
  @ Inputs: vector of datarows
  @ Function: Printout ofthe data
*/
void printData(vector<dataRow> d){
    for(int i = 0; i < d.size(); ++i){
      dataRow dr = d[i];
      printf("Attributes = ");
      for(int j = 0; j < dr.attributes.size(); ++j){
        printf("%d, ", dr.attributes[j]);
      }
      printf("res = %d\n",dr.result);
    }
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
    std::cerr << "You must enter two datasets, the training set and the test set, and a k value\n";
  }
  else{
    trainingFile = *(argv+1);
    trainingData = parseFile(trainingFile, 1);

    testFile = *(argv+2);
    testData = parseFile(testFile, 0);

    cout << "Training Data \n";
    printData(trainingData);
    cout << "Test Data \n";
    printData(testData);

    
  }
  std::cout << "Closing...\n";
  return 0;
}



