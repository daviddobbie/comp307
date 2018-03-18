// Name of program mainreturn.cpp

#include <iostream>
using namespace std;

int parseFile(char* fileName){
  cout << "Parsing..."<< fileName;

  return 0;

}


int main(int argc, char** argv)
{
  char * trainingFile;
  char * testFile;
  if(argc != 3){
    cout << "You must enter two datasets, the training set and the test set";
  }
  else{
    trainingFile = *(argv+1);
    testFile = *(argv+1);
    parseFile(trainingFile);
  }

  return 0;
}



