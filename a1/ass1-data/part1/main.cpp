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
#include <set>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool DEBUG = true;



enum typeFlower { setosa = 0, versicolor = 1, virginica =2, unknown=3}; 

typedef struct
{
  int id;
  double sepalLength;
  double sepalWidth;
  double petalLength;
  double petalWidth;
  typeFlower type;
}plant;


typeFlower classifier(char* str);

/*
@Inputs: file name to be parse
@Function: parses the data provided in the file into the format required
            to apply the ML technqiue
*/
 vector<plant> parseFile(char* fileName, int isTraining){
  char* localName = fileName;

  char line[256];

  int iterId=0;

  vector<plant> v;

  std::cout << "Parsing..."<< localName<< "\n";

  FILE * inFile;
  inFile = fopen(localName, "r");

  if(!inFile){

    std::cout << "Opening file failed\n";
    return v;
  }

  // parse thru each line, returns it as a string
  while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
      if(DEBUG) printf("%s",line);
      char * ptr;

      plant p;
      p.id = iterId;    

      //extracts out the doubles number by number.
      p.sepalLength = strtod(line, &ptr);
      p.sepalWidth = strtod(ptr, &ptr);    
      p.petalLength = strtod(ptr, &ptr); 
      p.petalWidth = strtod(ptr, &ptr);

      //prevents loading of the test set of data
      if(isTraining){
         p.type = classifier(ptr);
      }
      else{ 
        p.type=unknown;
      }

      //diagnostic print out of data stored
      if(DEBUG)
        printf("%d, %lf %lf %lf %lf %i\n", p.id, 
        p.sepalLength, p.sepalWidth, p.petalLength, p.petalWidth, (int)p.type);

      iterId ++;
      if (p.sepalLength != 0.0 && p.sepalWidth != 0.0 && p.petalLength != 0.0 && p.petalWidth !=0.0){ 
        v.push_back(p);
      }
  }

  fclose(inFile);
  std::cout << "Parsing "<< localName<< " Complete \n";
  return v;

}
/*
@Inputs: char string of flower code
@Functions: converts from string to enum
*/
typeFlower classifier(char* str){
  std::string s(str);

  if(s.find("setosa") != std::string::npos){
    return setosa;
  }
  else if(s.find("versicolor") != std::string::npos){
    return versicolor;
  }
  else if(s.find("virginica") != std::string::npos){
    return virginica;
  }
  return unknown;  
}


/*
@Inputs: vector of plants to print out
@Function: prints out all of the plants on the vector, used for diagnostics
*/
int printPlantVector(vector<plant> v){
  cout << "Printing out whole vector\n";
  for(int i=0; i< v.size(); ++i)
    printf("%d, %lf %lf %lf %lf %i\n", v[i].id, v[i].sepalLength, v[i].sepalWidth,
     v[i].petalLength, v[i].petalWidth,(int)v[i].type);

return 1;
}


/*
@Inputs: command arguments: the dataset to be parse and read from
@Function: to initialise the datasets in the program to be processed
*/
int main(int argc, char** argv)
{
  char * trainingFile;
  char * testFile;


  vector<plant> trainedPlants;
  vector<plant> testPlants;
  vector<plant> testPlantsAnswers;

  if(argc != 3){
    std::cerr << "You must enter two datasets, the training set and the test set\n";
  }
  else{
    trainingFile = *(argv+1);
    trainedPlants = parseFile(trainingFile, 1);

    testFile = *(argv+2);
    testPlants =  parseFile(testFile, 0);

    testPlantsAnswers = parseFile(testFile, 1);


    if(DEBUG){
      cout << "Printing vector of trained Plants \n";
      printPlantVector(trainedPlants);
      cout << "Printing vector of test plants \n";
      printPlantVector(testPlants);
      cout << "Printing vector of test plants answers\n";
      printPlantVector(testPlantsAnswers);
    }
  }
  std::cout << "Closing...\n";
  return 0;
}



