/*
Name: David Dobbie

Answer for COMP307 - Introduction to Artifical Intelligence
Assignment 1 - Part 3
Perceptron
*/


using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool DEBUG = false;

/*
    The class object of an instance
*/
class Instance{
    public:  
    int id = 0;
    int category;
    vector<bool> vals;


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
    void clearCategory(){
        category = 0; //reinitialises to 0
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

vector<Instance> parseFile(char* fileName, int isTraining){
    vector<Instance> vList;
    char* localName = fileName;
    char line[1024];
    int iterId=0;
    int catRead = '\0';
    int lineNo = 0;
    std::cout << "Parsing..."<< localName<< "\n";
    FILE * inFile;
    inFile = fopen(localName, "r");
    if(!inFile){
        std::cout << "Opening file failed\n";
        return vList;
    }

    // parse thru each line, returns it as a string
    while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
        //printf("Line: %s",line);
        vector<bool> loadedBoolList;
        int instCatRead=0;
        stringstream lineStr(line); 
        string word;
        //parses through line by line, pushes to respective stacks, etc.
        while(lineStr >> word){
            if(DEBUG)cout<<"Parsed Word: "<<word<<"\n";
        }
        lineNo++;
        }

    fclose(inFile);
    std::cout << "Parsing "<< localName<< " Complete \n";
    return vList;
}

int main(int argc, char** argv)
{
    char * trainingFile;
    char * testFile;

    int numCategories;
    int numAtts;
    vector<Instance> trainData;
    vector<Instance> testData;
    vector<Instance> testAnswers;

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
    trainData = parseFile(trainingFile, 1);

    testFile = *(argv+2);
    testData =  parseFile(testFile, 0);

    testAnswers = parseFile(testFile, 0);


    return 0;
 
}