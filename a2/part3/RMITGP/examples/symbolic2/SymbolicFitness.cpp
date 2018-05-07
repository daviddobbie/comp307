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


const int SymbolicFitness::FITNESS_CASES = 699;
const int SymbolicFitness::NUM_TEST_CASES = 1000;

SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{
   xValues = new double[FITNESS_CASES*9];
   targetFunc = new double[FITNESS_CASES];
   generationCounter = 0;
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
      std::string fileName;
      while (true) {
            cout << "Please enter file name for your data: ";
            getline(cin, input);

            // This code converts from string to number safely.
            stringstream myStream(input);
            if (myStream >> fileName)
            break;
            cout << "Invalid filename, please try again" << endl;
      }

      const char *localName = fileName.c_str();

      char line[1024];

      int iterID=0;

      std::cout << "Parsing..."<< localName<< "\n";

      FILE * inFile;
      inFile = fopen(localName, "r");

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
            //extracts out the doubles number by number.
            /*
            while (*ptr == ' '){ ptr ++;}
            double xVal = strtod(line, &ptr);
            while (*ptr == ' '){ ptr ++;}
            double yVal = strtod(line, &ptr);  
*/
            //sscanf(line, "%*[^0-9]%lf%*[^0-9]%lf", &xVal, &yVal);
            std::cout << str << "\n";
            //xVal = strtod(line, &ptr); 


            int pushIndx = -1; // to ignore the ID on the csv file
            while(std::getline(ss,cell, ',')) //parse comma sep. values
            {
                  std::cout << "parsing line\n";
                  if (pushIndx >= 0 && pushIndx < 9){
                        xVal = atof(cell.c_str());
                        //std::cout << 9*(iterID) + pushIndx;
                        xValues[9*(iterID) + pushIndx] = xVal;
                        printf("x=%lf\n", xVal);
                  }
                  else if(pushIndx == 9)
                  {
                        yVal = atof(cell.c_str());
                        //std::cout << (iterID);
                        printf("y=%lf\n", yVal);
                        targetFunc[iterID] = yVal;
                  }
                  pushIndx ++;
            }
            /*
            for(int i = 0; i < 9; ++i){
                  xVal = strtod(line, &ptr); 
                  xValues[9*(iterID-2) + i] = xVal; //for several inputs
                  printf("x=%lf",xVal);
            }
            printf("\n");
            */
            //xValues[iterID] = xVal;
            //targetFunc[iterID] = yVal;
            //printf("xVal = %f, yVal = %f\n", xValues[iterID-2], targetFunc[iterID-2]);
            iterID ++;
      }
      //SymbolicFitness::FITNESS_CASES = iterID -2;
      fclose(inFile);
      std::cout << "Parsing "<< localName<< " Complete \n";

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

void SymbolicFitness::outputResults(GeneticProgram *program, const char *filename)
{
   int i;
   double CTDouble;
   ofstream outputFile;
   string progString;
   ReturnDouble rd;

   outputFile.open(filename); 
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
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() < 1)
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
