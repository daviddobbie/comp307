/*
Name: David Dobbie

Answer for COMP307 Assignment 1 - Part 1
Nearest Neighbour Method
*/

#include <iostream>
using namespace std;


/*
@Inputs: file name to be parse
@Function: parses the data provided in the file into the format required
            to apply the ML technqiue
*/

int parseFile(char* fileName){
  cout << "Parsing..."<< fileName << "\n";

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
    cout << "You must enter two datasets, the training set and the test set";
  }
  else{
    trainingFile = *(argv+1);
    parseFile(trainingFile);

    testFile = *(argv+2);
    parseFile(testFile);
  }

  return 0;
}



