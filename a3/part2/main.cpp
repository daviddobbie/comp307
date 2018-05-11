/*
Name: David Dobbie

Answer for COMP307 - Introduction to Artifical Intelligence
Assignment 3 - Part 2
Naive Bayes
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

typedef struct{
  vector<int> attributes;
  int result;
} dataRow;


typedef struct{
  vector<double> probOfAttribute; //probability of result
  int givenResult;
} probability;

vector<dataRow> trainingData;
vector<dataRow> testData;

/*
@Inputs: file name to be parse
@Function: poarses the file and returns a table of data
*/
vector<dataRow> parseFile(char* fileName, int isTraining){
  char* localName = fileName;

  char line[256];

  int iterId=0;

  vector<dataRow> tableData;

  std::cout << "Parsing..."<< localName<< "\n";

  FILE * inFile;
  inFile = fopen(localName, "r");

  if(!inFile){

    std::cout << "Opening file failed\n";
    return tableData;
  }

  // parse thru each line, returns it as a string
  while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop
      if(DEBUG) printf("%s",line);
      dataRow d;
      char * ptr = line;
      int count = 0;
      while (*ptr != '\0')
      {   
          //if(DEBUG) printf("%c\n",*ptr);
          if(*ptr != ' ')
          {
            if (count < 12){
                d.attributes.push_back((int)*ptr - '0');
                count ++;
            } 
            else{
              if(isTraining == 1) d.result = (int)*ptr - '0';
              else d.result = 0; // default to classify as not spam for the test set
              break; // reached the end
            }
          }
          ptr ++;
      }
      tableData.push_back(d);

  }

  fclose(inFile);
  std::cout << "Parsing "<< localName<< " Complete \n";
  return tableData;

}

/*
  @ Inputs: vector of datarows
  @ Function: Printout ofthe data
*/
void printData(vector<dataRow> d){
    for(int i = 0; i < d.size(); ++i){
      dataRow dr = d[i];
      printf("Data point %d = {", i );
      for(int j = 0; j < dr.attributes.size(); ++j){
        printf("%d, ", dr.attributes[j]);
      }
      printf("} result = %d\n",dr.result);
    }
}

/*
  @ Inputs: vector of datarows
  @ Function: Printout ofthe data
*/
void printProb(probability p){
    for(int i = 0; i < p.probOfAttribute.size(); ++i){
      printf("P(P_%d=1|c=%d) = %llf\n", i, p.givenResult , p.probOfAttribute[i]);
    }
    printf("\n");
}




/*
Inputs: vector of data rows ,what given result we are looking for
functions: the probability such of each attribute for a given result
*/
probability calcIndependentProbs(vector<dataRow> dataTable, int givenResult){
  probability p;
  dataRow dr;
  int totalCount = 0;
  for (int attribIndx = 0; attribIndx < 12; attribIndx ++){ //go thru each attribute, add up result of 1
    p.probOfAttribute.push_back(0); //init at 0    
  }
  //cout << "Size of attribute vector = " << p.probOfAttribute.size() << "\n";
// ------------------------
  p.givenResult = givenResult; //since we are counting based on a result value
    for (int dataIndx = 0; dataIndx < dataTable.size(); dataIndx ++){
      dr = dataTable[dataIndx];
      //cout << "Data point result is = " << dr.result << "\n";
      //printf("Difference is = %d\n", dr.result - givenResult);
      //cout << "Given result to analyse is = " << givenResult << "\n";
        if(dr.result - givenResult == 0){
          //cout << "Total count = " << totalCount  << "\n";
          totalCount ++;
            for (int attribIndx = 0; attribIndx < dr.attributes.size(); attribIndx ++){ //go thru each attribute, add up result of 1
                p.probOfAttribute[attribIndx] = p.probOfAttribute[attribIndx] + dr.attributes[attribIndx];
            }
        }
  }
// ----------------------
  for (int attribIndx = 0; attribIndx < p.probOfAttribute.size(); attribIndx ++){ //go thru each attribute, add up result of 1
    if (p.probOfAttribute[attribIndx] == 0) p.probOfAttribute[attribIndx] = 1; //prevent a zero probability on each attribute
    p.probOfAttribute[attribIndx] = p.probOfAttribute[attribIndx] / double(totalCount);
  }


  return p;
}

/*
@ Inputs: probability given result = 0, prob given result = 1, data row
@ Functions: returns the class that the data row is to be classified into
*/
int bayesianClassifier(probability pGiven0, probability pGiven1, dataRow d){
  int result = 0; // default to classify for 0 - NOT SPAM
  double likelihoodIs0 = 1;
  double likelihoodIs1 = 1;


  double probExtract = 0.0;


  // testing viability for result being 0
  for (int idx = 0; idx < 12; ++idx){
      if (d.attributes[idx] == 0) probExtract = 1 - pGiven0.probOfAttribute[idx];
      else probExtract = pGiven0.probOfAttribute[idx];

      likelihoodIs0 = likelihoodIs0 * probExtract;
  } 

  // testing viability for result being 1
  for (int idx = 0; idx < 12; ++idx){
      if (d.attributes[idx] == 0) probExtract = 1 - pGiven1.probOfAttribute[idx]; //use complement value
      else probExtract = pGiven1.probOfAttribute[idx];

      likelihoodIs1 = likelihoodIs1 * probExtract;
  } 
  cout << "Likelihood for result = 0 is " << likelihoodIs0 << "\n";
  cout << "Likelihood for result = 1 is " << likelihoodIs1 << "\n";  
  if (likelihoodIs1 > likelihoodIs0) return 1;
  if (likelihoodIs0 > likelihoodIs1) return 0;

  return result;
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
    std::cerr << "You must enter two datasets, the training set and the test set, and a k value\n";
  }
  else{
    trainingFile = *(argv+1);
    trainingData = parseFile(trainingFile, 1);

    testFile = *(argv+2);
    testData = parseFile(testFile, 0);
/*
    cout << "Training Data \n";
    printData(trainingData);
    cout << "Test Data \n";
    printData(testData);
*/
    cout << "Probability of results given class is 1\n";
    probability pResult1 = calcIndependentProbs(trainingData, 1);
    printProb(pResult1);
    cout << "Probability of results given class is 0\n";
    probability pResult0 = calcIndependentProbs(trainingData, 0);
    printProb(pResult0);

    
    for(int i = 0; i < testData.size(); ++i){
      testData[i].result = bayesianClassifier(pResult0, pResult1, testData[i]);
    }

    cout << "Classified test data \n";
    printData(testData);

    
  }
  std::cout << "Closing...\n";
  return 0;
}



