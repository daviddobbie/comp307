/*
Name: David Dobbie

Answer for COMP307 - Introduction to Artifical Intelligence
Assignment 1 - Part 3
Perceptron
*/


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

using namespace std;


class Image;
class Feature;

bool DEBUG = false;



/*
    Establishes the feature class
*/
class Feature{
    public:
    vector<int> row;
    vector<int> col;
    vector<bool> sgn;   
    bool value;


    Feature(int rowsMax, int colsMax, int numRndPxls){ //assume they are all 10x10
        for (int i = 0; i < numRndPxls; ++i){
            row.push_back(rand() % rowsMax);
            col.push_back(rand() % colsMax);
            sgn.push_back(rand() % 2);
        }
    }
    void printFeature(){
        cout << "Feature values {row,col,sgn} = ";
        for(int i = 0; i<row.size(); ++i){
            printf("{%d, %d, %d} ", row[i], col[i], (int)sgn[i]);
        }
        cout << "\n";
    }
    Feature(){ //creates dummy feat
        value=1;
    }
};

/*
    The class object of an Image
*/
class Image{
    public:
    int id = 0;
    string categoryName;
    int rows;
    int cols;
    vector<vector<bool>> matrix;
    vector<bool> featVectValues;
    /*
        @Inputs: none
        @Functions: Prints out image and other diagnostic data
    */
    void printImage(){
        cout<< "Rows: " << rows << " Cols: " << cols << "\n";
        cout << "Image Id: "<< id << "\n";
        cout << "Image Type: " << categoryName << "\n";
        cout << "featVectValues: ";
        for(bool b:featVectValues) cout << b;
        cout << "\n";
        for(int r = 0; r<rows; ++r){
            for(int c = 0; c<cols ; ++c){
                if (matrix[r][c]) cout << (char)254u;
                else cout << " ";
            }
        cout << "|\n";
        }
    }
    void clearImage(){
        categoryName.clear();
        rows = 0;
        cols = 0;
        matrix.clear();
    }

    bool setValueInput(Feature f){
        int value = 0;
        if (f.row.empty()) return true;
        int sum = 0;
        for(int i = 0; i< f.row.size(); ++i){
            if(matrix[f.row[i]][f.col[i]] == f.sgn[i]) sum ++;
        }
        value = (sum >=3)?1:0;
        return value;
    }

    void setFeatVectValues(vector<Feature> featVect){
        for(int i= 0; i < featVect.size(); ++i){
            featVectValues.push_back(setValueInput(featVect[i]));
        }
        //cout << "Length of valueVect = " << featVectValues.size() << "\n";
        return;
    }
    void printfeatVectValues(){
        //cout << "Length of valueVect = " << featVectValues.size() << "\n";
        for(int b: featVectValues){
            cout << b;
        }
    }
};


typedef struct{
    vector<Feature> featVect;
    vector<double> weightVect;
}Perceptron;

/*
    @Inputs: Take vector of bool data stream, no of rows, no of cols
    @Function: Convert it to a matrix of data, image
*/
vector<vector<bool>> convertBoolToImage(vector<bool> data, int rows, int cols){
    vector<vector<bool>> m;
    vector<bool> tempCol;
    for(int r = 0; r<rows; ++r){
        for(int c = 0; c<cols ; ++c){
            //cout << "data index = " << r*cols +c << "\n";
            //cout << "resulting data = " << data[r*cols +c] << "\n";
            tempCol.push_back(data[r*cols + c]);
        }
        m.push_back(tempCol);
    }
    return m;
}



/*
    @Inputs: takes in file name
    @Function: Parses out data into a vector of different images being tested
*/
vector<Image> parseFile(char* fileName){
    vector<Image> vList;
    Image loadingImage;
    vector<bool> dataQueue;

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
                if(DEBUG)cout << "Detected P1 file \n";
                //finished parsing last image
                if(!dataQueue.empty() && loadingStage >=3){
                    if(DEBUG)cout << "data queue length: " <<  dataQueue.size() << "\n";
                    if(DEBUG)cout<< "Rows: " << loadingImage.rows << " Cols: " << 
                    loadingImage.cols << "\n";
                    /*
                    for(bool b: dataQueue){
                        cout<< b;
                    }
*/
                    loadingImage.matrix = convertBoolToImage(dataQueue, 
                        loadingImage.rows, loadingImage.cols);
                    vList.push_back(loadingImage);
                    if(DEBUG)cout << "Pushed Id: " << loadingImage.id << "\n";
                    dataQueue.clear();
                }
                loadingStage = 0;
            }
            else if(loadingStage == 0){ //writing category to image
                if(DEBUG)cout << "Loading category name \n";
                loadingStage ++;
                word.erase(0,1); //removes # comment
                loadingImage.categoryName = word;
                loadingImage.id = iterId;
                iterId++;
            }
            else if(loadingStage == 1){ //recording rows and cols
                if(DEBUG)cout << "Loading rows and cols \n";
                loadingStage ++;
                loadingImage.rows = stoi(line);
                loadingImage.cols = stoi(line);
            }
            else if(loadingStage >= 2){ //recording data of rows and cols
                if(DEBUG)cout << "Loading data \n";
                loadingStage ++;
                for(char& c : word){
                    if(DEBUG)cout << (bool)c;
                    if(c == '1') dataQueue.push_back(true);
                    else dataQueue.push_back(false);
                }
            }
        }
        lineNo++;
    }
    fclose(inFile);
    std::cout << "Parsing "<< localName<< " Complete \n";
    return vList;
}

/*
    @Inputs:
    @Functions:
*/
int neuralNetworkLearning(){
    
}


int main(int argc, char** argv)
{
    char * file;

    int numCategories;
    int numAtts;

    vector<Image> trainData;
    Perceptron p;
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
    trainData = parseFile(file);
    
    //adds dummy feature to it.
    Feature dummy_f = Feature();
    p.featVect.push_back(dummy_f);
    p.weightVect.push_back(1);

    //load feature vector mapping.
    for(int i = 0; i< 49; ++i){
        Feature f = Feature(10,10,4); //assume 10 rows, 10 cols, 4 rnd positions
        p.featVect.push_back(f);
        p.weightVect.push_back(1);
    }

    //load feature vector values for each image
    for(int i = 0; i < trainData.size(); ++i){
        trainData[i].setFeatVectValues(p.featVect);
        trainData[i].printfeatVectValues();
    }
    // prints each features mapping to an image.
    for(Feature f:p.featVect){
        f.printFeature();
    }

    for (Image t:trainData){
        t.printImage();
    }

    return 0;
 
}