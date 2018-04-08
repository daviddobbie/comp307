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


typedef struct{
    vector<int> row;
    vector<int> col;
    vector<bool> sgn;   
}feature;

/*
    The class object of an Image
*/
class Image{
    public:
    string categoryName;
    int rows;
    int cols;
    vector<vector<int>> matrix;
};

vector<Image> parseFile(char* fileName, int isTraining){
    vector<Image> vList;
    Image loadingImage;

    // different loading stages:
        // 0 = P1
        // 1 = category
        // 2 = rows and cols
        // 3 = image data
    int loadingStage = 0; 

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
        stringstream lineStr(line); 
        string word;
        //parses through line by line, pushes to respective stacks, etc.
        while(lineStr >> word){
            if(DEBUG)cout<<"Parsed Word: "<<word<<"\n";
            if(word=="P1"){
                if (loadingStage ==3)vList.push_back(loadingImage);
                loadingStage = 0;
            }
            else if(loadingStage == 0){ //writing category to image
                loadingStage ++;
                loadingImage.categoryName = word;
            }
            else if(loadingStage == 1){ //recording rows and cols
                loadingStage ++;
                lineStr >> loadingImage.rows;
                lineStr >> loadingImage.cols;
            }
            else if(loadingStage == 2){ //recording data of rows and cols
                loadingStage ++;

            }
        }
        lineNo++;
    }

    fclose(inFile);
    std::cout << "Parsing "<< localName<< " Complete \n";
    return vList;
}

int main(int argc, char** argv)
{
    char * file;

    int numCategories;
    int numAtts;

    vector<Image> trainData;

    /*
    vector<bool> dataVect;
    dataVect.push_back(true);
    Image newImage(2, dataVect);
    */


    if(argc != 2){
        std::cerr << "You must enter one file name\n";
        return 1;
    }


    file = *(argv+1);
    trainData = parseFile(file, 1);


    return 0;
 
}