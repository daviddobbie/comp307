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

#include "SymbolicFitness.h"
#include "ReturnInt.h"
#include "XInt.h"

#include "GPConfig.h"
#include <cmath>

const int SymbolicFitness::FITNESS_CASES = 20;

SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{
   xValues = new int[FITNESS_CASES];
   targetFunc = new int[FITNESS_CASES];
}

SymbolicFitness::~SymbolicFitness()
{
   delete [] xValues;
   delete [] targetFunc;
}

void SymbolicFitness::initFitness()
{
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
            char * ptr;
                  printf("%s\n",line);

            std::string str(line);
            stringstream ss(str);

            if (iterID > 1){
                  float xVal;
                  float yVal;
                  //extracts out the doubles number by number.
                  /*
                  while (*ptr == ' '){ ptr ++;}
                  double xVal = strtod(line, &ptr);
                  while (*ptr == ' '){ ptr ++;}
                  double yVal = strtod(line, &ptr);  
*/
                  //sscanf(line, "%*[^0-9]%lf%*[^0-9]%lf", &xVal, &yVal);


                  xVal = (int)strtod(line, &ptr);
                  yVal = (int)strtod(ptr, &ptr);  
                  printf("x=%f, y=%f\n",xVal, yVal);



                  xValues[iterID-2] = xVal;
                  targetFunc[iterID-2] = yVal;

                  printf("xVal = %f, yVal = %f\n", xValues[iterID-2], targetFunc[iterID-2]);
            }
            iterID ++;
      }
      //SymbolicFitness::FITNESS_CASES = iterID -2;
      fclose(inFile);
      std::cout << "Parsing "<< localName<< " Complete \n";

   /*
   for(i=0; i<FITNESS_CASES; i++)
   { 
      xValues[i] = config->randomNumGenerator->randNum() % 200;
      //targetFunc[i] = xValues[i] + xValues[i] + xValues[i] + 14;
      targetFunc[i] = (3 * (xValues[i] * xValues[i]) / (xValues[i] + 2))
                      + (4 * xValues[i]) -127;
                        
   }
   */
}

void SymbolicFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i,j;
   ReturnInt ri;


   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      for(j=0; j<FITNESS_CASES; j++)
      {
         XInt::setValue(xValues[j]);
         pop[i]->evaluate(&ri);
         pop[i]->setFitness(pop[i]->getFitness() + 
                            fabs(targetFunc[j] - ri.getData()));
      }
   }
}

bool SymbolicFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.000001)
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
