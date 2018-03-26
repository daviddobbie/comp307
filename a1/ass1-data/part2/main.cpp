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
    Instance(int cat, vector<bool> v)
    {
        if(DEBUG) cout << "Created a new instance\n";
        id +=1;
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
@Inputs: command arguments: the dataset to be parse and read from
@Function: to initialise the datasets in the program to be processed
*/
int main(int argc, char** argv)
{
    int numCategories;
    int numAtts;

    vector<string> categoryNames;
    vector<string> attNames;
    vector<Instance> allInstances;

    /*
    vector<bool> dataVect;
    dataVect.push_back(true);
    Instance newInstance(2, dataVect);
    */


    if(argc != 3){
        std::cerr << "You must enter two datasets, the training set and the test set\n";
    }
    return 1;


    
}