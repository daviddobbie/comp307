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

bool DEBUG = false;
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
    Instance(int identify, int cat, vector<bool> v)
    {
        //if(DEBUG) cout << "Created a new instance\n";
        id =identify;
        category =cat;
        vals = v;

    }
    bool getAtt(int index){
        return vals[index];
    }
    int getCategory(){
        return category;
    }
    void printInst(){
        cout << "Instance ID = " << id<< "; category = " << category;
        cout << "; Boolean List = ";
        for(int i=0; i< vals.size(); ++i){
            if (vals[i]) cout << " true";
            if (!vals[i]) cout << " false";                     
        }
        cout << "\n";
        return;
    }

};

/*
*/
typedef struct{
  vector<Instance> instList;
  vector<string> catNameList;
  vector<string> attNameList;
}dataSetStruct;

/*
    Input: category name vector, word to compare with
    Function: converts the string type to an int, reduces computation intenisty of comparing
*/
int catStringToInt(vector<string> catNameList, string word){
    for (int i=0; i < catNameList.size(); ++i){
        if(word==catNameList[i])
            return i;
    }

    return 0;
}

/*
@Inputs: file name to be parse
@Function: parses the data provided in the file into the format required
            to apply the ML technqiue
*/
 dataSetStruct parseFile(char* fileName, int isTraining){
  char* localName = fileName;
  char line[256];
  int iterId=0;
  int catRead = '\0';

  int lineNo = 0;

  dataSetStruct ds;


  std::cout << "Parsing..."<< localName<< "\n";
  FILE * inFile;
  inFile = fopen(localName, "r");
  if(!inFile){
    std::cout << "Opening file failed\n";
    return ds;
  }

  // parse thru each line, returns it as a string
  while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
      if(DEBUG) printf("%s",line);
      
      vector<bool> loadedBoolList;
      int instCatRead=0;

      stringstream lineStr(line); 
      string word;


      //parses through line by line, pushes to respective stacks, etc.
      while(lineStr >> word){
        if(DEBUG)cout<<"Parsed Word: "<<word<<"\n";

        if(lineNo==0) ds.catNameList.push_back(word); //if 1st row, we have the column headers of categories
        else if(lineNo==1) ds.attNameList.push_back(word); //if 2nd row, we have the column headers of attributes
        else{ 
            if(word=="true"){
                loadedBoolList.push_back(true);
                if(DEBUG)cout<<"Pushed: "<<word<<"\n";
            }
            else if(word=="false"){
                loadedBoolList.push_back(false);
                if(DEBUG)cout<<"Pushed: "<<word<<"\n";
            }
            else{
                instCatRead = catStringToInt(ds.catNameList,word);
            }
        }
      }
      
      lineNo++;
      if(lineNo>2){ //ignores lines that had no category read
        Instance inst(iterId, instCatRead, loadedBoolList);
        //diagnostic print out of data stored
        if(DEBUG) inst.printInst();

        ds.instList.push_back(inst);
        iterId ++;
    }
  }

  fclose(inFile);
  std::cout << "Parsing "<< localName<< " Complete \n";
  return ds;

}



/*
    Inputs: dataSetStruct with attributeNames, InstanceList, and the categoryNames
    Function: prints out full dataset in its raw form
*/
int printDS(dataSetStruct ds){
    cout << "Attribute Names:\n"; 
    for(int i = 0; i<ds.attNameList.size(); ++i){
        cout <<  ds.attNameList[i] << "\t";
    }
    cout << "\n Category Names:\n"; 
    for(int i = 0; i<ds.catNameList.size(); ++i){
        cout <<  ds.catNameList[i] << "\t";
    }
    cout << "\n";
    cout << "Instance List:\n"; 
    for(int i = 0; i<ds.instList.size(); ++i){
        ds.instList[i].printInst();
    }


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

    int numCategories;
    int numAtts;

    dataSetStruct training;
    dataSetStruct testing;


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
    training = parseFile(trainingFile, 1);

    printDS(training);

    testFile = *(argv+2);
    testing =  parseFile(testFile, 0);
    return 0;

    
}