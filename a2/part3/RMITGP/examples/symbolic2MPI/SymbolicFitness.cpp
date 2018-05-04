/******************************************************************************
 Definition file
 Class:        SymbolicFitness
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <float.h> //for DBL_MAX
#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>

#include "SymbolicFitness.h"
#include "ReturnDouble.h"

#include "XDouble.h"

#ifdef MPI_ENABLED
#include "mpi.h"
#endif

const int SymbolicFitness::FITNESS_CASES = 50;
const int SymbolicFitness::NUM_TEST_CASES = 1000;

SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{
   xValues = new double[FITNESS_CASES];
   targetFunc = new double[FITNESS_CASES];
   generationCounter = 0; 
}

SymbolicFitness::~SymbolicFitness() 
{
   delete [] xValues;
   delete [] targetFunc;
}

void SymbolicFitness::initFitness()
{
   int i;
   for(i=0; i<FITNESS_CASES; i++)
   {
      xValues[i] = (config->randomNumGenerator->randReal() * 200) - 100;
      // 1.5X^3 + 3.2X^2 + 4.0X - 127.2
      targetFunc[i] = (1.5 * (xValues[i] * xValues[i] * xValues[i])) +
                      (3.2 * (xValues[i] * xValues[i])) +
                      (4.0 * xValues[i]) -127.2;
   }
   

}

void SymbolicFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
#ifdef MPI_ENABLED // If MPI is enabled this will change to a master/slave process as below

	int MPI_count = 0;
	MPI_Comm_size(MPI_COMM_WORLD,&MPI_count);
	if(MPI_count > 1)
	{
		masterProcess(pop, popSize);
		return;
	}
#endif

   int i,j;
   ReturnDouble rd;

   for(i=0; i<popSize; i++)
   {
      pop[i]->setFitness(0.0);
      for(j=0; j<FITNESS_CASES; j++)
      {
         XDouble::setValue(xValues[j]);
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
			if (!_finite(rd.getData())||!_finite(pop[i]->getFitness()+fabs(targetFunc[j] - rd.getData())))
#else
			if (!std::isfinite(rd.getData())||!std::isfinite(pop[i]->getFitness()+fabs(targetFunc[j] - rd.getData())))
#endif
         {
            pop[i]->setFitness(this->worst());
            continue;         
         }
         else
         {
            pop[i]->setFitness(pop[i]->getFitness() + 
                               fabs(targetFunc[j] - rd.getData()));
         }
      }
   }

}

void SymbolicFitness::outputResults(GeneticProgram *program, const char *filename)
{
   int i;
   double xDouble;
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
      xDouble = (double)i;
      XDouble::setValue(xDouble);

      program->evaluate(&rd);
      
      outputFile << xDouble << " "
   //            << (3 * xDouble) + 14.45 << " "
                 << (1.5 * (xDouble * xDouble * xDouble)) +
                    (3.2 * (xDouble * xDouble)) +
                    (4.0 * xDouble) -127.2 << " "
                 << rd.getData() << endl;
   }

   outputFile.close();
}

bool SymbolicFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.0001)
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


///////////////////////////////////////////////////////////////////////
// MPI Processing Section - Master and slave have different processes
// Master mutates and assigns programs to slaves who process and return relevant values
// to the Master
///////////////////////////////////////////////////////////////////////

#ifdef MPI_ENABLED
void SymbolicFitness::masterProcess(GeneticProgram* pop[], int popSize)
{
  int process = 0;
  int popNum = 0;
  int currentPop;
  double fitness;
  int MESSAGE_SIZE = 10000;
  char message[MESSAGE_SIZE];
  int processSize;
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD,&processSize);
  process = processSize-1;
  
  string programString="";
  stringstream ss("");
 
  for(int i=1;i<processSize;i++) // sends programs to the slave processors
  {
    string programString = "";
	programString = "";
    pop[popNum]->print(programString);
    ss << popNum << " " << programString<<'\0';
	ss.read(message,MESSAGE_SIZE);
	//cout<<"Message Sent: "<<message<<"\n Sent to: "<< i<<" "<<popNum<<" "<<programString<<endl;
	MPI_Send(&message,MESSAGE_SIZE,MPI_CHAR,i,1,MPI_COMM_WORLD);
	//cout<<"Messent sent"<<endl;
	popNum++;
	ss.clear();
	ss.str("");
  }
  while (popNum < popSize) // Wait for a slave to finish, process it, then send it another
  {
    MPI_Recv(&message,MESSAGE_SIZE,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	ss << message;
	ss >> process >> currentPop >> fitness;
	pop[currentPop]->setFitness(fitness);
	ss.clear();
	ss.str("");
	programString = "";
    pop[popNum]->print(programString);
    ss << popNum << " " << programString<<'\0';
	ss.read(message,MESSAGE_SIZE);
	//cout<<message<<endl;
	MPI_Send(&message,MESSAGE_SIZE,MPI_CHAR,process,1,MPI_COMM_WORLD);
	popNum++;
	ss.clear();
	ss.str("");
   }
   while (processSize > 1) // Once all programs have been sent, wait for last program results to be returned
   {
    MPI_Recv(&message,MESSAGE_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	ss << message;
	ss >> process >> currentPop >> fitness;
	pop[currentPop]->setFitness(fitness);
	processSize--;
	ss.clear();
	ss.str("");
   }
}


void SymbolicFitness::slaveProcess(GeneticProgram* pop)
{
	int rank = 0;
	int popNum = 0;
	int currentPop;
	double fitness;
	int MESSAGE_SIZE = 10000;
	char message[MESSAGE_SIZE];  
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	string programString="";
	stringstream ss(""); 

	while(1) // Wait for master instructions
	{
		ss.clear();
		ss.str("");
		programString = "";
		MPI_Recv(&message,MESSAGE_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		ss << message;
		ss >> currentPop;
		if (currentPop == -1) // termination message
		{
			return;
		}
		getline(ss,programString);
		programString.erase(0,1);
		pop->parseProgram(programString);
		int falseneg = 0,falsepos =0, trueneg =0, truepos = 0;
		programString = "";
		pop->print(programString);	
		
		//Process the program as per the normal version:
  	    int j;
		ReturnDouble rd;

	    pop->setFitness(0.0);
		for(j=0; j<FITNESS_CASES; j++)
		{
			XDouble::setValue(xValues[j]);
			pop->evaluate(&rd);
			
			
#ifdef WIN32
			if (!_finite(rd.getData())||!_finite(pop->getFitness()+fabs(targetFunc[j] - rd.getData())))
#else
			if (!std::isfinite(rd.getData())||!std::isfinite(pop->getFitness()+fabs(targetFunc[j] - rd.getData())))
#endif
			{
				pop->setFitness(this->worst()); 
			}
			else
			{
				pop->setFitness(pop->getFitness() + 
					   fabs(targetFunc[j] - rd.getData()));
			}
		}

	ss.clear();
	ss.str("");	
	ss << rank <<" "<< currentPop <<" "<< pop->getFitness()<<'\0';
	ss.read(message, MESSAGE_SIZE);
	MPI_Send (&message, MESSAGE_SIZE, MPI_CHAR,0,1,MPI_COMM_WORLD);	
	 }
}
#endif


