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
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool DEBUG = false;

typedef struct{
    int category;
    double prob;
}catProb;

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

class Node{
    public:
        Node* left = nullptr;
        Node* right = nullptr;
        bool isLeaf = false;
        int category = 0;
        string bestAttribute = "";
        double probAttrib = 0.00;

        Node (){
        }
        void setLeft(Node * n){
            left = n;
        }
        void setRight(Node *n){
            right = n;
        }
        void setAttribute(string at){
            bestAttribute = at;
        }
        void debugPrint(){
            cout << "NODE DEBUG WORKS\n";
        }
};


vector<Instance> bestTrueInstance;
vector<Instance> bestFalseInstance;
string bestGlobalAttribute = "";
double bestWeightedAvgImpurity = 2000;


/*
*/
typedef struct{
  vector<Instance> instList;
  vector<string> catNameList;
  vector<string> attNameList;
}dataSetStruct;
/*
    @Inputs: the list of instances
    @Function: returns the probalilty of the modal attribute in the instance list
*/

double instListAttributeProb(vector<Instance> instList){
    map<vector<bool>, int> instMap;
    int max = 0;
    for(int i = 0; i<instList.size(); ++i){
        vector<bool> vb = instList[i].vals;
        if(instMap.count(vb)>0){
            instMap[vb] +=1;
            if(instMap[vb] > max){
                max = instMap[vb];
            }
        }else{
            instMap.insert(pair<vector<bool>,int>(vb, 1));
        }
    }
    return (double)(max)/(double)(instList.size());
}

/*
    @Inputs: the list of instances
    @Function: returns the probalilty of the modal category in the instance list
*/
catProb instListCategoryProb(vector<Instance> instList){
    catProb cp;
    map<int, int> instMap;
    int max = 0;
    int modeCat = 0;
    for(int i = 0; i<instList.size(); ++i){ //iterate through each instance
        int cat = instList[i].category;
        if(instMap.count(cat)>0){
            instMap[cat] +=1;
            if(instMap[cat] > max){
                max = instMap[cat];
                modeCat = cat;
            }
        }else{
            instMap.insert(pair<int,int>(cat, 1));
        }
    }
    cp.category = modeCat;
    cp.prob = (double)(max)/(double)(instList.size());

    return cp;
}
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
@Inputs: file name to be parsed
@Function: parses the data provided in the file into the format required
            to apply the ML technqiue
*/
 dataSetStruct parseFile(char* fileName, int isTraining){
  char* localName = fileName;
  char line[1024];
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
      //printf("Line: %s",line);
      
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
    @Inputs: instance set
    @Function: computes the purity of a set of instances based on categories
*/
double computeImpurity(vector<Instance> v){
    double impurity = 0;
    int total = v.size();
    map<int, int> instMap; //key is the category id, value is the count of them
    for(int i = 0; i<total; ++i){ //iterate thru categories
        int cat = v[i].category;
        if(instMap.count(cat)>0){
            instMap[cat] += 1;
        }else{
            instMap.insert(pair<int,int>(cat, 1));
        }
    }
    for(int i = 0; i<instMap.size(); ++i){
        impurity = impurity + instMap[i]/total;
    }

    return 2*impurity;
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
    @Inputs: set of instances still at the node, and list of attributes still present
    @Function: builds the decision tree using the information given
*/
Node* BuildTree(dataSetStruct ds, int modeCategory, double modeProb){
    Node *n = new Node();
    int modeCat = instListCategoryProb(ds.instList).category;
    double modeCatProb = instListCategoryProb(ds.instList).prob;
    if(ds.instList.empty()){//no more instances to classifym make leaf node
        cout << "1. No more instances to make, this node is a leaf\n";
        (*n).category = modeCategory;
        (*n).probAttrib = modeProb;
        (*n).isLeaf = true;
        //cout << "Probability of Category: " << (*n).probAttrib 
        //<< "  The category: " << (*n).category << "\n";   
        return n;      
    }
    if(modeCatProb >= 1.00){ //all instances pure, make leaf node
        cout << "2. All instances are pure, this node is a leaf\n";
        (*n).probAttrib =1.00;
        (*n).bestAttribute = ds.catNameList[modeCat];
        (*n).category = modeCategory;   
        (*n).isLeaf = true;  
        cout << "Probability of Category: " << (*n).probAttrib 
        << "  The category: " << (*n).category << "\n";    
        return n;
    }
    if(ds.attNameList.empty()){//run out of attributes to branch off, make impure
        cout << "3. Ran out of attributes to branch off, making impure leaf\n";
        (*n).probAttrib = instListCategoryProb(ds.instList).prob;
        (*n).bestAttribute = ds.catNameList[modeCat];
        (*n).category = modeCat;  
        (*n).isLeaf = true; 
        //cout << "Probability of Category: " << (*n).probAttrib 
        //<< "  The category: " << (*n).category << "\n";  

        return n;
    }
    else{ //find the best attribute to split on
        cout << "4. Figuring out the best attribute to split on\n";
        (*n).isLeaf = false;
        for(int i = 0; i < ds.attNameList.size(); ++i){
            //separate instances into two sets based on results
            vector<Instance> resultTrue;
            vector<Instance> resultFalse;  

            for(int j = 0; j < ds.instList.size(); ++j){
                //printf("Attribute Name=%s, True/False=%d\n", ds.attNameList[i].c_str(), (int)ds.instList[j].vals[i]);
                if(ds.instList[j].vals[i]){ //peek the attributes of the data
                    resultTrue.push_back(ds.instList[j]);
                }else{
                    resultFalse.push_back(ds.instList[j]);
                }
            }

            //compute the weighted purity of each set
            double trueFract = (double)resultTrue.size()/(double)ds.instList.size();
            double falseFract = (double)resultFalse.size()/(double)ds.instList.size();           
            double impurityTrue = computeImpurity(resultTrue)*trueFract;
            double impurityFalse = computeImpurity(resultFalse)*falseFract;
            double weightedAvgImpurity = impurityTrue + impurityFalse;
            //printf("Purity Stats: %llf, %llf, %llf, %llf, %llf\n", trueFract, falseFract, impurityTrue, impurityFalse, weightedAvgImpurity);
            if (weightedAvgImpurity < bestWeightedAvgImpurity){ //decides best
                //printf("Changing Best Attribute\n");
                bestGlobalAttribute = ds.attNameList[i];
                cout << bestGlobalAttribute << "\n";
                bestTrueInstance = resultTrue;
                bestFalseInstance = resultFalse;
                //printf("Loaded best attribute\n");
            }
        }
        //build the next subtrees with remianing attributes
        vector<string> newAttributes = ds.attNameList;
        newAttributes.erase(remove(newAttributes.begin(), newAttributes.end(), bestGlobalAttribute)
                        , newAttributes.end());
        printf("Removed best attribute\n");
        dataSetStruct newDSTrue;
        dataSetStruct newDSFalse;

        newDSTrue.instList = bestTrueInstance;
        newDSTrue.attNameList = newAttributes;
        newDSTrue.catNameList = ds.catNameList;

        //printDS(newDSTrue);

        newDSFalse.instList = bestFalseInstance;
        newDSFalse.attNameList = newAttributes;
        newDSFalse.catNameList = ds.catNameList;
        //printf("Making Node\n");
        std::cout << "attribute=" << bestGlobalAttribute << "\n";
        //(*n).debugPrint();

        (*n).setAttribute(bestGlobalAttribute);
        //printf("Set Node's Attribute\n");
        (*n).setLeft(BuildTree(newDSTrue, modeCategory, modeProb));
        //printf("Started left branch\n");
        (*n).setRight(BuildTree(newDSFalse, modeCategory, modeProb));
        //printf("Started right branch\n");
        printf("Made Node\n");
        return n;
    }

    return nullptr;
}

/*
    Input: node, int depth
    Output: recursively print out the whole tree
*/
void printNode (Node*n, int depth, int ifLeft){
    for(int i = 0; i < depth; ++i){
        cout << "\t";
    }
    Node * ln = (*n).left;
    Node * rn = (*n).right;
    if(ln != nullptr){
        if(!(*ln).isLeaf) cout << (*ln).bestAttribute << " = true \n";
        else cout << "Class " << (*ln).category << ", prob = " << (*ln).probAttrib << "\n"; 
        printNode((*n).left, depth + 1, 1);
    }
    if(rn != nullptr){
        if(!(*rn).isLeaf) cout << (*rn).bestAttribute << " = false \n";
        else cout << "Class " << (*rn).category  << ", prob = " << (*rn).probAttrib << "\n"; 
        printNode((*n).right, depth + 1, 0);
    }
}


/* @Inputs: the pointer to the datastruct of all of the datasets vectors
   @Function: clears all of the categories in the data set, removing the answers
*/
int clearAnswers(dataSetStruct *ds){
    for(int i = 0; i<(*ds).instList.size(); ++i){
        (*ds).instList[i].clearCategory();
        cout << (*ds).instList[i].getCategory() <<"\n";
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

    dataSetStruct trainData;
    dataSetStruct testData;
    dataSetStruct testAnswers;


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

    clearAnswers(&testData);
/*
    cout << "Opening Test Dataset...\n";
    printDS(testData);
    cout << "Opening Training Dataset...\n";   
    printDS(trainData);
    cout << "Opening Answers Dataset...\n";  
    printDS(testAnswers);
*/
    if(DEBUG){
        cout << instListAttributeProb(trainData.instList) << "\n";
        cout << "cat="<< instListCategoryProb(trainData.instList).category <<
        " p= "<< instListCategoryProb(trainData.instList).prob << "\n";
    }


    catProb cp = instListCategoryProb(trainData.instList);
    cout << "Prob Mean";
    Node * rootNode = BuildTree(trainData, cp.category, cp.prob);

    printNode(rootNode, 0,1);
    return 0;
 
}