/*
Name: David Dobbie

Answer for COMP307 - Introduction to Artifical Intelligence
Assignment 1 - Part 2
Decision Tree Learning Method
*/


using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool DEBUG = true;



/*
    The class object of an instance
*/
class Instance{
    private:
    int id = 0;
    int category;
    vector<bool> vals;

    public:
    /*
    Inputs: category type, ordered vector of booleans
    Function: initalises the 
    */
    Instance(int i, int cat, vector<bool> v)
    {
        //if(DEBUG) cout << "Created a new instance\n";
        id =i;
        category =cat;
        vals = v;

    }
    bool getAtt(int index){
        return vals[index];
    }
    int getCategory(){
        return category;
    }

};

/*
@Inputs: file name to be parse
@Function: parses the data provided in the file into the format required
            to apply the ML technqiue
*/
 vector<Instance> parseFile(char* fileName, int isTraining){
  char* localName = fileName;
  char line[256];
  int iterId=0;
  int catRead;

  bool isFirstLine = true;

  vector<bool> valsRead;

  vector<Instance> vInst;
  vector<string> catNames;
  vector<string> attNames;


  std::cout << "Parsing..."<< localName<< "\n";
  FILE * inFile;
  inFile = fopen(localName, "r");
  if(!inFile){
    std::cout << "Opening file failed\n";
    return vInst;
  }

  // parse thru each line, returns it as a string
  while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
      if(DEBUG) printf("%s",line);
      
      
      stringstream lineStr(line); 
      string word;
      
      while(lineStr >> word){
        if(DEBUG)cout<<"Parsed Word: "<<word<<"\n";
        if(isFirstLine) attNames.push_back(word);

      }

      if(isFirstLine) isFirstLine=false; //finishes reading first line

      Instance inst(iterId, catRead, valsRead);
      //diagnostic print out of data stored
      vInst.push_back(inst);
  }

  fclose(inFile);
  std::cout << "Parsing "<< localName<< " Complete \n";
  return vInst;

}


/*
@Inputs: command arguments: the dataset to be parse and read from
@Function: to initialise the datasets in the program to be processed
*/
int main(int argc, char** argv)
{
    char * trainingFile;
    char * testFile;

    int numCategories;
    int numAtts;

    vector<string> categoryNames;
    vector<string> attNames;
    vector<Instance> trainingInstances;
    vector<Instance> testInstances;

    /*
    vector<bool> dataVect;
    dataVect.push_back(true);
    Instance newInstance(2, dataVect);
    */


    if(argc != 3){
        std::cerr << "You must enter two datasets, the training set and the test set\n";
        return 1;
    }

    trainingFile = *(argv+1);
    trainingInstances = parseFile(trainingFile, 1);

    testFile = *(argv+2);
    testInstances =  parseFile(testFile, 0);
    return 0;

    
}