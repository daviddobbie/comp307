/*****************************************************************************
 Definition file
 Class:        ClassificationFitness
 Date created: 29/03/2006
 Written by:   Djaka W Kurniawan 
 Date Modified: 18/07/2007 
 Modified by:   Danny Fang
 Date Modified: 06/03/2013 
 Modified by:   Geoff Lee
 
 Modified by Perry Barile: the modifications by Fang were written using C89. I
 modified that code to make it conform to the C++ standard and to make the code
 easier to understand.
 
 See header file for details
 *****************************************************************************/

using namespace std;

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>

#include "ClassificationFitness.h"
#include "ReturnDouble.h"
#include "Attribute.h"

#include "GPConfig.h"

extern vector<double> pixelValues;
extern vector<vector<double> > data;
extern int nOfImages;
extern char *dataClassification;
int currentImage;

// For visual display results per generation
static int numGen = 0;
static double currFitness = 100.0;


ClassificationFitness::ClassificationFitness(GPConfig *conf) : Fitness(conf)
{
	if(TARPEIAN)
	{
		conf->activateTarpeian(this); // QCS 20121012
	}
    if(DDL) 
	{
   	   conf->activateDDL(this); // QCS 20121012
   	   conf->ddl->setHeavy(true); // QCS 20121012
   	   conf->ddl->setVeryHeavy(true); // QCS 20121012
	}
}

ClassificationFitness::~ClassificationFitness()
{
}

void ClassificationFitness::initFitness()
{
	
}

/*
 Modifications by Perry Barile
 
 - Replaced usage of variable names i, j and k with meaningful context-sensitive
 names.
 
 - Declared variable names in their local scope instead of at the start of the
 method. This is good programming style. Declaring variables at the start of a
 method can make debugging difficult or at least confusing. E.g. the int 
 ""segmentation is declared and later set to 1, but the rest of the code that
 uses that variable is commented out. (Segmentation variable has been removed).
 */

/*
 Assign Fitness is called by the evolution portion of the RMITGP function.
 This is the user defined portion of what defines the fitness of a program.
*/ 
void ClassificationFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
	int totpos = 0;
	int totneg = 0;
	string programString; 
		
#ifdef MPI_ENABLED // If MPI is enabled this will change to a master/slave process as below
	int MPI_count = 0;
	MPI_Comm_size(MPI_COMM_WORLD,&MPI_count);
	if(MPI_count > 1)
	{
		masterProcess(pop, popSize);
		return;
	}
#endif
	// Determine total positive and negative functions in the data file
	for (int k=0;k<nOfImages; k++)
	{
		if(dataClassification[k] == 'T')
		{
			totpos++;
		} else {
			totneg++;
		}
	}	
	ReturnDouble rd;
	
	for (int popMember = 0; popMember < popSize; popMember++)
	{
		pop[popMember]->setFitness(100.0);
	}
	
	// Choose the type of selection to be used
	if (DYNAMIC_SELECTION)
	{
		for(int popMember = 0; popMember < popSize; popMember++)
		{		
			dynamicSelection(pop[popMember], totpos, totneg);
		}		
    }
    else
    {
		for(int popMember = 0; popMember < popSize; popMember++)
		{
			normalSelection(pop[popMember], totpos, totneg);		
		}
	}
	
    // For visual logging
    double bestLocalFitness = 100.0;
    for (int popMember = 0; popMember < popSize; popMember++)
    {
		double fitness = pop[popMember]->getFitness();
		if (fitness < bestLocalFitness)
			bestLocalFitness = fitness;
    }
	
    if (bestLocalFitness < currFitness)
    {
		cout << "Gen: " << numGen << "\tFitness: " << bestLocalFitness << endl;
		currFitness = bestLocalFitness;
    }
    else if (numGen % 10 == 0)
	cout << "Gen: " << numGen << endl;
	
    numGen++;
}

 /**********************************
 Normal Selection produces a positive result if the GP is greater than 0,
 and negative if it is less than 0. Only useful for binary classifications.
 **********************************/
void ClassificationFitness::normalSelection(GeneticProgram* pop, int totpos, int totneg)
{
	char range[502];  
    float fitness;
	int falseneg = 0,falsepos =0, trueneg =0, truepos = 0;
	ReturnDouble rd;
	
	for (int imageNum = 0; imageNum < nOfImages; imageNum++)
	{
		pixelValues.clear();
		for(int pixelNum = 0; pixelNum<(int)data[imageNum].size(); pixelNum++)
			pixelValues.push_back(data[imageNum][pixelNum]);
		
		char classification = 'T';
		rd.setData(0);	
		pop->evaluate(&rd);
		
#ifdef WIN32 
			if (!_isnan(rd.getData()))
#else
			if (!isnan(rd.getData()))
#endif
			{
				if (rd.getData() >= 0) {
					classification = 'T';
					if (dataClassification[imageNum] == classification) {
						truepos++;
					} else {
						falsepos++;
					}
				} else {
					classification = 'F'; 
					if (dataClassification[imageNum] == classification) {
						trueneg++;
					} else {
						falseneg++;
					}
				}
		}
	}
	fitness = 100 - ((float)truepos/totpos* 50.0+(float)trueneg/totneg*50);

	range[0] = '0';
	range[1] = '\0';	
	pop->setFitness(fitness);
	pop->setObjectiveValue(0,(float)falsepos/totneg*100);
	pop->setObjectiveValue(1,(float)falseneg/totpos*100);	
	pop->setRange(range);
}
 
 /**********************************
 Dynamic Selection is an advanced method of selection whereit creates an int array 
 of 500, and examines where in the range the data falls for each pop. It then classifies each 
 section of the range based on how many positive/negatives fell in that zone, and 
 uses those zones instead of a simple less than/greater than range.

 Technically, it runs the algoirthms twice. In the first pass, it calculates where in the range
 it lands. It then classifies that range as positive or negative based on the total results.
 If the were no results in the range or the results were equal, then it will use neigbouring
 results to classify the zone.
 In the second pass the data is then categorised as positive or negative based on the 
 categorised range it lands in.
 **********************************/
void ClassificationFitness::dynamicSelection(GeneticProgram* pop, int totpos, int totneg)
{ 

	char range[502];  
    float fitness;
	int falseneg = 0,falsepos =0, trueneg =0, truepos = 0;
	ReturnDouble rd;
	
	int gpOutputs[501][2];
	char newrange[502];
	string str1;
	int dataClass;
	
	int* results = new int[nOfImages];
	
	range[501]='\0';
	newrange[501] = '\0';
	
	for (int rangeIndex = 0; rangeIndex < 501; rangeIndex++)
	{
		gpOutputs[rangeIndex][0] = 0;
		gpOutputs[rangeIndex][1] = 0;
	}

	for (int imageNum = 0; imageNum < nOfImages; imageNum++)
	{
		pixelValues.clear();
		currentImage=imageNum;
		for(int pixelNum = 0; pixelNum < (int)data[imageNum].size(); pixelNum++)
			pixelValues.push_back(data[imageNum][pixelNum]);
		
		pop->evaluate(&rd);
		
			int rounded = (int)round(rd.getData());
			//cout << "The individual "<< popMember<<" the "<<imageNum<<" time result is "<<rounded<<endl;
			
			if (rounded < -250)
				rounded = -250;
			if (rounded > 250)
				rounded = 250;
			results[imageNum] = rounded;
			
			dataClass = 0;
			if (dataClassification[imageNum] == 'T') dataClass = 1;
			gpOutputs[rounded+250][dataClass]++;
	}
	
	// Assign either a 0 or a 1 to each range index. Assign a ? if there
	// is a problem.
	for (int rangeIndex = 0; rangeIndex < 501; rangeIndex++)
	{
		float adjustment = 1;
		if (totpos != totneg) adjustment = (float)totneg/(float)totpos; 
		float output0 = gpOutputs[rangeIndex][0];
		float output1 = gpOutputs[rangeIndex][1]*adjustment;
		
		if (output0 == 0 && output1 == 0)
			range[rangeIndex] ='?'; 
		else if (output0 > output1)
			range[rangeIndex] = '0';
		else 
			range[rangeIndex] = '1';
	}
	// 0 1 2 3 4 5 6 7 8 9
	// 0 0 1 0 0 ? ? 0 0 1
	// ri 4
	// t1 3
	// t2 6
	for (int rangeIndex = 0; rangeIndex < 501; rangeIndex++)
	{
		newrange[rangeIndex] = range[rangeIndex];
		if (range[rangeIndex]=='?')
		{
			int temp1 = rangeIndex;
			
			while (temp1 > 0 && range[temp1] == '?')
				temp1--;
			
			if (range[temp1] == '?' && temp1 == 0) 
				temp1 = rangeIndex;
			
			int temp2 = rangeIndex;
			
			while (temp2 < 500 && range[temp2] == '?')
				temp2++;
			
			if (range[temp2] == '?' && temp2 == 500) 
				temp2 = rangeIndex;
			
			if ((rangeIndex - temp1) > (temp2 - rangeIndex))
				newrange[rangeIndex] = range[temp1];
			else
				newrange[rangeIndex] = range[temp2];
		}
		if (newrange[rangeIndex] == '?') newrange[rangeIndex] = '1';
	}
	strcpy(range, newrange);
	
	for (int imageNum = 0; imageNum < nOfImages; imageNum++)
	{
			int rounded = results[imageNum];//(int)round(rd.getData());
			// magic number 48 is to convert the ascii character into the number 0 or 1
			int dataClassificationForImage = dataClassification[imageNum];
			int convertedAsciiNum = (int)(range[rounded+250]-48);

			if (dataClassificationForImage == 'T')//real
			{
				if (convertedAsciiNum == 1) 
				{
					truepos++;//true positive
				}
				else
					falseneg++;//false negtive
			}
			else // dataClassificationForImage == 0
			{
				if (convertedAsciiNum == 0)
				{
					trueneg++; //true negtive
				}
				else
					falsepos++;//false positive
			}
	}

	fitness = 100 - ((float)truepos/totpos* 50.0+(float)trueneg/totneg*50);
	pop->setFitness(fitness);
	pop->setObjectiveValue(0,(float)falsepos/totneg*100);
	pop->setObjectiveValue(1,(float)falseneg/totpos*100);	
	pop->setRange(range);	

}
 

bool ClassificationFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
	
	for (int i = 0; i < popSize; i++)
	{
		if (pop[i]->getFitness() == 0.00)
		return true;
	}
	return false;
}

bool ClassificationFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
	if (!EMO)
		return (gp1->getFitness() < gp2->getFitness());

	int objective1Squared, objective2Squared;
	objective1Squared = pow(gp1->getObjectiveValue(0),2)+pow(gp1->getObjectiveValue(1),2);
	objective2Squared = pow(gp2->getObjectiveValue(0),2)+pow(gp2->getObjectiveValue(1),2);
	return (objective1Squared < objective2Squared);	
}

bool ClassificationFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
	if (!EMO)
		return (gp1->getFitness() > gp2->getFitness());
		
	int objective1Squared, objective2Squared;
	objective1Squared = pow(gp1->getObjectiveValue(0),2)+pow(gp1->getObjectiveValue(1),2);
	objective2Squared = pow(gp2->getObjectiveValue(0),2)+pow(gp2->getObjectiveValue(1),2);
	return (objective1Squared > objective2Squared);			
}

bool ClassificationFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
	if (!EMO)
		return (gp1->getFitness() == gp2->getFitness());

	int objective1Squared, objective2Squared;
	objective1Squared = pow(gp1->getObjectiveValue(0),2)+pow(gp1->getObjectiveValue(1),2);
	objective2Squared = pow(gp2->getObjectiveValue(0),2)+pow(gp2->getObjectiveValue(1),2);
	return (objective1Squared == objective2Squared);		
}

double ClassificationFitness::best()
{
    return 0.0;
}

double ClassificationFitness::worst()
{
    return 100.0;
}

///////////////////////////////////////////////////////////////////////
// MPI Processing Section - Master and slave have different processes
// Master mutates and assigns programs to slaves who process and return relevant values
// to the Master
///////////////////////////////////////////////////////////////////////

#ifdef MPI_ENABLED
void ClassificationFitness::masterProcess(GeneticProgram* pop[], int popSize)
{
  int process = 0;
  int popNum = 0;
  int currentPop;
  float fitness, falsepos, falseneg;
  int MESSAGE_SIZE = 10000;
  char message[MESSAGE_SIZE], range[502];
  int processSize;
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD,&processSize);
  process = processSize-1;
  
  string programString="";
  stringstream ss("");
  
  for(int i=1;i<processSize;i++) // sends programs to the slave processors
  {
    programString = "";
    pop[popNum]->print(programString);
    ss << popNum << " " << programString<<'\0';
	ss.read(message,MESSAGE_SIZE);
	//cout<<"Message Sent: "<<message<<"\n Sent to: "<< i<<" "<<popNum<<" "<<programString<<endl;
	MPI_Send(&message,MESSAGE_SIZE,MPI_CHAR,i,1,MPI_COMM_WORLD);
	popNum++;
	ss.clear();
	ss.str("");
  }
  while (popNum < popSize) // Wait for a slave to finish, process it, then send it another
  {
    MPI_Recv(&message,MESSAGE_SIZE,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	ss << message;
	//cout << message<<endl;
	ss >> process >> currentPop >> fitness >> falsepos >> falseneg >> range;
	pop[currentPop]->setFitness(fitness);
	pop[currentPop]->setObjectiveValue(0,falsepos);
	pop[currentPop]->setObjectiveValue(1,falseneg);
	pop[currentPop]->setRange(range);
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
	ss >> process >> currentPop >> fitness >> falsepos >> falseneg>>range;
	pop[currentPop]->setFitness(fitness);
	pop[currentPop]->setObjectiveValue(0,falsepos);
	pop[currentPop]->setObjectiveValue(1,falseneg);
	pop[currentPop]->setRange(range);  
	processSize--;
	ss.clear();
	ss.str("");
   }
	// Master/Slave relationship complete, master compiles results
    double bestLocalFitness = 100.0;
    for (int popMember = 0; popMember < popSize; popMember++)
    {
		double fitness = pop[popMember]->getFitness();
		cout << "Fitness: " << fitness <<endl;
		if (fitness < bestLocalFitness)
			bestLocalFitness = fitness;
    }
	
    if (bestLocalFitness < currFitness)
    {
		cout << "Gen: " << numGen << "\tFitness: " << bestLocalFitness << endl;
		currFitness = bestLocalFitness;
    }
    else if (numGen % 10 == 0)
		cout << "Gen: " << numGen << endl;
    cout<<"Generation "<<numGen<<" timestamp: "<<(time(NULL)-run_time)<<endl;	
    numGen++;
}


void ClassificationFitness::slaveProcess(GeneticProgram* pop)
{
	int totpos = 0;
	int totneg = 0;
	int rank = 0;
	int popNum = 0;
	int currentPop;
	float fitness, ffalsepos, ffalseneg;
	int MESSAGE_SIZE = 10000;
	char message[MESSAGE_SIZE], range[502];  
	string programString;
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
	for (int k=0;k<nOfImages; k++)
	{
		if(dataClassification[k] == 'T')
		{
			totpos++;
		} else {
			totneg++;
		}
	}	
	stringstream ss; 

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
		if (!DYNAMIC_SELECTION)
		{
			normalSelection(pop, totpos, totneg);
		}
		else // DYNAMIC_SELECTION
		{
			dynamicSelection(pop, totpos, totneg);
		}

		string range1;
		ss.clear();
		ss.str("");	
		pop->printRange(range1);
		ss << rank <<" "<< currentPop <<" "<< pop->getFitness() <<" "<< pop->getObjectiveValue(0) <<" "<< pop->getObjectiveValue(1) <<" "<< range1 <<'\0';
		ss.read(message, MESSAGE_SIZE);
		MPI_Send (&message, MESSAGE_SIZE, MPI_CHAR,0,1,MPI_COMM_WORLD);	
	 }
}
#endif
