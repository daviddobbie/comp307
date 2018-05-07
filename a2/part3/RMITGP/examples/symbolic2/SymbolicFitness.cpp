/******************************************************************************
 Definition file
 Class:        SymbolicFitness
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <float.h> //for DBL_MAX
#include <sstream>
#include <cmath>

#include <iostream>
#include <fstream>

#include "SymbolicFitness.h"
#include "ReturnDouble.h"
#include "ReturnInt.h"

#include "XDouble.h"


const int SymbolicFitness::FITNESS_CASES = 399;
const int SymbolicFitness::NUM_TEST_CASES = 200;
int GENERATION_COUNTER = 0;


SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{
   xValues = new double[FITNESS_CASES*9];
   targetFunc = new double[FITNESS_CASES];
   xTestValues = new double[NUM_TEST_CASES*9];
   targetTestFunc = new double[NUM_TEST_CASES];


   GENERATION_COUNTER = 0;
//   if(TARPEIAN) conf->activateTarpeian(this); // QCS 20120917
//   if(DDL) {
//	   conf->activateDDL(this); // QCS 20120923
//	   conf->ddl->setHeavy(true); // QCS 20121011
//	   conf->ddl->setVeryHeavy(true); // QCS 20121011
}

SymbolicFitness::~SymbolicFitness() 
{
   delete [] xValues;
   delete [] targetFunc;
   delete [] xTestValues;
   delete [] targetTestFunc;
}

void SymbolicFitness::initFitness()
{
   /*
   for(i=0; i<FITNESS_CASES; i++)
   {
      xValues[i] = (config->randomNumGenerator->randReal() * 200) - 100;
      // 1.5X^3 + 3.2X^2 + 4.0X - 127.2
      targetFunc[i] = (1.5 * (xValues[i] * xValues[i] * xValues[i])) +
                      (3.2 * (xValues[i] * xValues[i])) +
                      (4.0 * xValues[i]) -127.2;
   }
   */

      std::string input = "";
      std::string trainingFileName;
      std::string testFileName;     
      while (true) {
            cout << "Please enter file name for your TRAINING data: ";
            getline(cin, input);

            // This code converts from string to number safely.
            stringstream myStream(input);
            if (myStream >> trainingFileName)
            break;
            cout << "Invalid trainingFileName, please try again" << endl;
      }
      while (true) {
            cout << "Please enter file name for your TEST data: ";
            getline(cin, input);

            // This code converts from string to number safely.
            stringstream myStream(input);
            if (myStream >> testFileName)
            break;
            cout << "Invalid testFileName, please try again" << endl;
      }

      const char *localTrainName = trainingFileName.c_str();
      char line[1024];
      int iterID=0;
      std::cout << "Parsing..."<< localTrainName<< "\n";
      FILE * inFile;
      inFile = fopen(localTrainName, "r");
      if(!inFile){
            std::cout << "Opening file failed\n";
            return;
      }
      // parse thru each line, returns it as a string
      while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop

            std::string str(line);
            std::stringstream ss(str);
            std::string cell;

            double xVal;
            double yVal;
            //std::cout << str << "\n";

            int pushIndx = -1; // to ignore the ID on the csv file
            while(std::getline(ss,cell, ',')) //parse comma sep. values
            {
                  //std::cout << "parsing line\n";
                  if (pushIndx >= 0 && pushIndx < 9){
                        if (cell=="?") xVal = -1.0;
                        else xVal = atof(cell.c_str());
                        //std::cout << 9*(iterID) + pushIndx;
                        xValues[9*(iterID) + pushIndx] = xVal;
                        //printf("x=%lf\n", xVal);
                  }
                  else if(pushIndx == 9)
                  {
                        yVal = atof(cell.c_str());
                        //std::cout << (iterID);
                        //printf("y=%lf\n", yVal);
                        targetFunc[iterID] = yVal;
                  }
                  pushIndx ++;
            }
            iterID ++;
      }
      fclose(inFile);
      std::cout << "Parsing "<< localTrainName<< " Complete \n";

      // -----------------------------------------------------------------------------------
      //loading testing file name

      const char *localTestName = testFileName.c_str();

      iterID=0;
      std::cout << "Parsing..."<< localTestName<< "\n";
      inFile = fopen(localTestName, "r");
      if(!inFile){
            std::cout << "Opening file failed\n";
            return;
      }
      // parse thru each line, returns it as a string
      while (fgets(line, sizeof(line), inFile)) { // standard C I/O file reading loop

            std::string str(line);
            std::stringstream ss(str);
            std::string cell;

            double xVal;
            double yVal;
            //std::cout << str << "\n";

            int pushIndx = -1; // to ignore the ID on the csv file
            while(std::getline(ss,cell, ',')) //parse comma sep. values
            {
                  //std::cout << "parsing line\n";
                  if (pushIndx >= 0 && pushIndx < 9){
                        if (cell=="?") xVal = -1.0;
                        else xVal = atof(cell.c_str());
                        //std::cout << 9*(iterID) + pushIndx;
                        xTestValues[9*(iterID) + pushIndx] = xVal;
                        printf("x=%lf\n", xVal);
                  }
                  else if(pushIndx == 9)
                  {
                        yVal = atof(cell.c_str());
                        //std::cout << (iterID);
                        printf("y=%lf\n", yVal);
                        targetTestFunc[iterID] = yVal;
                  }
                  pushIndx ++;
            }
            iterID ++;
      }
      fclose(inFile);
      std::cout << "Parsing "<< localTestName<< " Complete \n";
}

void SymbolicFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i,j,k;
   ReturnDouble rd;

   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      for(j=0; j<FITNESS_CASES; j++)
      {
            //load all of the variable terminal nodes
            CTDouble::setValue(xValues[j*9]);
            USzDouble::setValue(xValues[j*9 + 1]);
            UShpDouble::setValue(xValues[j*9 + 2]);
            MADouble::setValue(xValues[j*9 + 3]);
            SESzDouble::setValue(xValues[j*9 + 4]);
            BNDouble::setValue(xValues[j*9 + 5]);
            BCDouble::setValue(xValues[j*9 + 6]);
            NNDouble::setValue(xValues[j*9 + 7]);
            MDouble::setValue(xValues[j*9 + 8]);

            pop[i]->evaluate(&rd);

            //Unfortunately we have to check for NaN
            //We should probably also check for Infinity but I'm not sure
            //of a portable way to do that.
            /*#ifdef WIN32
            if (_isnan(rd.getData()))
            #else
            if (isnan(rd.getData()))
            #endif*/
            #ifdef WIN32
                        if (!_finite(rd.getData()))
            #else
                        if (!std::isfinite(rd.getData()))
            #endif
            {
                  pop[i]->setFitness(this->worst());
                  continue;         
            }
            else
            {
                  /*
                  pop[i]->setFitness(pop[i]->getFitness() + 
                              
                              pow(fabs(targetFunc[j] - rd.getData()) , 2.0)    );
                              */
                  /*pop[i]->setFitness(pop[i]->getFitness() + 
                              fabs(targetFunc[j] - rd.getData())    );*/
                  if (targetFunc[j] == 4.0){
                        if(rd.getData() > 3){
                              pop[i]->setFitness(pop[i]->getFitness() + 0); //no addition to error
                        }else{
                              pop[i]->setFitness(pop[i]->getFitness() + 1); //addition to error since wrong classification
                        }
                  }
                  else{
                        if(rd.getData() > 3){
                              pop[i]->setFitness(pop[i]->getFitness() + 1); //addition to error since wrong classification
                        }else{
                              pop[i]->setFitness(pop[i]->getFitness() + 0); // no addition to error
                        }
                  }
            }           
      }
   }

}

void SymbolicFitness::testFitness(GeneticProgram* pop[], int popSize){
   int i,j,k;
   ReturnDouble rd;

   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      for(j=0; j<NUM_TEST_CASES; j++)
      {
            //load all of the variable terminal nodes
            CTDouble::setValue(xTestValues[j*9]);
            USzDouble::setValue(xTestValues[j*9 + 1]);
            UShpDouble::setValue(xTestValues[j*9 + 2]);
            MADouble::setValue(xTestValues[j*9 + 3]);
            SESzDouble::setValue(xTestValues[j*9 + 4]);
            BNDouble::setValue(xTestValues[j*9 + 5]);
            BCDouble::setValue(xTestValues[j*9 + 6]); 
            NNDouble::setValue(xTestValues[j*9 + 7]);
            MDouble::setValue(xTestValues[j*9 + 8]);

            pop[i]->evaluate(&rd);

            #ifdef WIN32
                        if (!_finite(rd.getData()))
            #else
                        if (!std::isfinite(rd.getData()))
            #endif
            {
                  pop[i]->setFitness(this->worst());
                  continue;         
            }
            else
            {
                  if (targetFunc[j] == 4.0){
                        if(rd.getData() > 3){
                              pop[i]->setFitness(pop[i]->getFitness() + 0); //no addition to error
                        }else{
                              pop[i]->setFitness(pop[i]->getFitness() + 1); //addition to error since wrong classification
                        }
                  }
                  else{
                        if(rd.getData() > 3){
                              pop[i]->setFitness(pop[i]->getFitness() + 1); //addition to error since wrong classification
                        }else{
                              pop[i]->setFitness(pop[i]->getFitness() + 0); // no addition to error
                        }
                  }
            }           
      }
   }   
}



void SymbolicFitness::outputResults(GeneticProgram *program, const char *trainingFileName)
{
   int i;
   double CTDouble;
   ofstream outputFile;
   string progString;
   ReturnDouble rd;

   outputFile.open(trainingFileName); 
   if (outputFile.bad())
   {
      cerr << "SymbolicFitness::outputResults Could not open output file"
           << endl;  
      return;
   }

   program->print(progString);

   outputFile << "#Results for evolved program" << endl  
              << "#Output" << endl 
              << "#X    Expected     Actual" << endl;

   for (i=0; i<NUM_TEST_CASES; i++)
   {
      CTDouble = (double)i;
      CTDouble::setValue(CTDouble);

      program->evaluate(&rd);
  /*    
      outputFile << CTDouble << " "
   //            << (3 * CTDouble) + 14.45 << " "
                 << (1.5 * (CTDouble * CTDouble * CTDouble)) +
                    (3.2 * (CTDouble * CTDouble)) +
                    (4.0 * CTDouble) -127.2 << " "
                 << rd.getData() << endl;
                 */
   }

   outputFile.close();
}

bool SymbolicFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   GENERATION_COUNTER ++;
   double bestFitness = 10000;
   double currFitness;

   double testBestFitness = 10000;
   double testCurrFitness;


   // training set fitness
   for (; i<popSize; i++)
   {
      currFitness = pop[i]->getFitness();
      if (currFitness < bestFitness)
         bestFitness = currFitness;
   }
   for (; i<popSize; i++)
   {
      currFitness = pop[i]->getFitness();
      if (currFitness < bestFitness)
         bestFitness = currFitness;
   }
   // test set fitness, use the test data set to set fitness

   //cout << "Test Set fitness \n";

   testFitness(pop, popSize);
   for (i = 0; i<popSize; i++)
   {
      testCurrFitness = pop[i]->getFitness();
      if (testCurrFitness < testBestFitness)
         testBestFitness = testCurrFitness;
   }
   for (; i<popSize; i++)
   {
      testCurrFitness = pop[i]->getFitness();
      if (testCurrFitness < testBestFitness)
         testBestFitness = testCurrFitness;
   }  

   std::cout << "gen = " << GENERATION_COUNTER << "; Train Fit = " << bestFitness << 
    "; Test Fit = "  << testBestFitness << "\n";
   if (currFitness < 1)
   {
         return true;
   }
   return false;
}

bool SymbolicFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool SymbolicFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}

bool SymbolicFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double SymbolicFitness::best()
{
   return 0.0;
}

double SymbolicFitness::worst()
{
   return DBL_MAX;
}
