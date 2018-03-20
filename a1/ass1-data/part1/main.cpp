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
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool DEBUG = false;

enum typeFlower { setosa = 0, versicolor = 1, virginica =2, unknown=3}; 

typedef struct{
  float max=0;
  float min=INFINITY;
  float range=0;
}stats;

typedef struct{
  stats sepalLength;
  stats petalLength;
  stats sepalWidth;
  stats petalWidth;
}measure;

typedef struct{
  int id;
  float dist;
  typeFlower type;
}flowerDist;

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
measure getVectorStats(vector<plant> v){
  measure vectorStats;

  for(int i=0; i< v.size(); ++i){
    vectorStats.sepalLength.max = fmaxf(vectorStats.sepalLength.max, v[i].sepalLength);
    vectorStats.sepalLength.min = fminf(vectorStats.sepalLength.min, v[i].sepalLength);

    vectorStats.petalLength.max = fmaxf(vectorStats.petalLength.max, v[i].petalLength);
    vectorStats.petalLength.min = fminf(vectorStats.petalLength.min, v[i].petalLength);

    vectorStats.sepalWidth.max = fmaxf(vectorStats.sepalWidth.max, v[i].sepalWidth);
    vectorStats.sepalWidth.min = fminf(vectorStats.sepalWidth.min, v[i].sepalWidth);

    vectorStats.petalWidth.max = fmaxf(vectorStats.petalWidth.max, v[i].petalWidth);
    vectorStats.petalWidth.min = fminf(vectorStats.petalWidth.min, v[i].petalWidth);
  }
  vectorStats.sepalLength.range = vectorStats.sepalLength.max - vectorStats.sepalLength.min;
  vectorStats.petalLength.range = vectorStats.petalLength.max - vectorStats.petalLength.min;
  vectorStats.sepalWidth.range = vectorStats.sepalWidth.max - vectorStats.sepalWidth.min;
  vectorStats.petalWidth.range = vectorStats.petalWidth.max - vectorStats.petalWidth.min;

  if(DEBUG){
    printf("Sepal Length: Max:%f, Min%f, Range:%f \n",vectorStats.sepalLength.max, vectorStats.sepalLength.min, vectorStats.sepalLength.range);
    printf("Petal Length: Max:%f, Min%f, Range:%f \n",vectorStats.petalLength.max, vectorStats.petalLength.min, vectorStats.petalLength.range);  
    printf("Sepal Width: Max:%f, Min%f, Range:%f \n",vectorStats.sepalWidth.max, vectorStats.sepalWidth.min, vectorStats.sepalWidth.range);
    printf("Petal Width: Max:%f, Min%f, Range:%f \n",vectorStats.petalWidth.max, vectorStats.petalWidth.min, vectorStats.petalWidth.range);
  }


  return vectorStats;
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
Comparator of the distance measure struct
*/
bool compareByDist(flowerDist &a, flowerDist &b)
{
    return a.dist < b.dist;
}

/*
@Inputs: k long vector of distances and IDs (the closest)
@Function: Figures out dominant type in classification, returns it
*/
typeFlower voteClassify(vector<flowerDist> v){
  int countFlower [3] = {0,0,0};

  for(int i=0; i< v.size(); ++i){
      if(v[i].type==setosa) countFlower[0] = countFlower[0]+1;
      if(v[i].type==virginica) countFlower[1] = countFlower[1]+1;
      if(v[i].type==versicolor) countFlower[2] = countFlower[2]+1;
  }
  int largestIndex = 0;
  int countMax = 0;
  for(int i = 0; i < 3; i++){
    if(countFlower[i]>countMax){
      largestIndex = i;
      countMax = countFlower[i];
    }
    //if there is an equal amount, give a 50/50 choice that next one beats it
    else if(countFlower[i]==countMax){
      if(rand()%100 > 50){
        largestIndex = i;
        countMax = countFlower[i];
      }
    }
  }
  switch(largestIndex){
    case 0:
      return setosa;
    case 1:
      return virginica;
    case 2:
      return versicolor;
  }
  return unknown;
}

/*
@Inputs: testing plant, vector of trained plants, k value, attributes of training set
@Function: Calculate distance of plant from trained plants, return k smallest,
            then assign the majority one to the tested plant
@Return: the type that the test plant is classified into.
*/
typeFlower nearestNeighbour(plant t, vector<plant> v, int k, measure trainedStats){
  vector<flowerDist> distVector;
  flowerDist distCurrentFlower;

  distCurrentFlower.dist = 0.0;

  vector<int> closest;


  float sepalLengthDiffNorm = 0.0;
  float sepalWidthDiffNorm = 0.0;
  float petalLengthDiffNorm = 0.0;
  float petalWidthDiffNorm = 0.0;

  for(int i=0; i< v.size(); ++i){
      distCurrentFlower.dist = 0;
      distCurrentFlower.id = v[i].id;
      distCurrentFlower.type = v[i].type;
      //calculates distance of test plant with all trained plants
      sepalLengthDiffNorm = pow((v[i].sepalLength - t.sepalLength),2)/pow(trainedStats.sepalLength.range,2);
      sepalWidthDiffNorm = pow((v[i].sepalWidth - t.sepalWidth),2)/pow(trainedStats.sepalWidth.range,2);
      petalLengthDiffNorm = pow((v[i].petalLength - t.petalLength),2)/pow(trainedStats.petalLength.range,2);
      petalWidthDiffNorm = pow((v[i].petalWidth - t.petalWidth),2)/pow(trainedStats.petalWidth.range,2);

      distCurrentFlower.dist = sqrt(sepalLengthDiffNorm + sepalWidthDiffNorm + petalLengthDiffNorm + petalWidthDiffNorm);

      distVector.push_back(distCurrentFlower);
      if(DEBUG)printf("%d, %f\n", distCurrentFlower.id, distCurrentFlower.dist);
  }

  //sort by smallest distances
  std::sort(distVector.begin(), distVector.end(), compareByDist);

  //extract 5 smallest values
  vector<flowerDist> kVector(distVector.begin(), distVector.begin()+(k)); 

  if(DEBUG){
    for(int i=0; i< kVector.size(); ++i){
      printf("%d, %f\n", kVector[i].id, kVector[i].dist);
    }
  }
  return voteClassify(kVector);
}
/*
@Inputs: 2 vectors of the test set, one being sorted by nearestNeighbour, the other being the answer set.
@Function: Compares the answers and the results to assess the accuracy of it, returns float on accuracy
*/
float assessResults(vector<plant> answers, vector<plant> results){
  float error = 0;
  float size = (float)answers.size();
    for(int i=0; i< answers.size(); ++i){
      if (answers[i].type!=results[i].type) error = error +1.0;
    }
  return (1.0 - error/size);
}




/*
@Inputs: command arguments: the dataset to be parse and read from
@Function: to initialise the datasets in the program to be processed
*/
int main(int argc, char** argv)
{
  char * trainingFile;
  char * testFile;
  measure trainedStats;

  int k;

  vector<plant> trainedPlants;
  vector<plant> testPlants;
  vector<plant> testPlantsAnswers;

  if(argc != 4){
    std::cerr << "You must enter two datasets, the training set and the test set, and a k value\n";
  }
  else{
    trainingFile = *(argv+1);
    trainedPlants = parseFile(trainingFile, 1);

    testFile = *(argv+2);
    testPlants =  parseFile(testFile, 0);

    k = stoi(*(argv+3));


    testPlantsAnswers = parseFile(testFile, 1);

    trainedStats = getVectorStats(trainedPlants);
    cout << "Started classification of the test dataset\n";
    //executes nearest Neighbour on the test set, wrties the new type to it
    for(int i=0; i< testPlants.size(); ++i){
        testPlants[i].type = nearestNeighbour(testPlants[i],trainedPlants, k, trainedStats);
    }
    cout << "Finished classification of the test dataset\n";
    cout << "Percentage of correct classification = " << assessResults(testPlantsAnswers,testPlants) << "\%\n";

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



