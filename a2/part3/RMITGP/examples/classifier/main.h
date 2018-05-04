using namespace std;

#include "Population.h"
#include "EMOPopulation.h"

#include "Fitness.h"

#include "GeneticProgram.h"

#include "NodeSet.h"
#include "ProgramGenerator.h"

#include "Attribute.h"
//#include "TempTerminalC.h"
//#include "TempTerminalD.h"
#include "RandDouble.h"
#include "RandInt.h"
#include "RandSOperation.h"
//#include "RandTIndex.h"
//#include "RandTOperation.h"
#include "RandVIndex.h"

#include "Coordinate.h"
#include "Rect.h"

#include "PlusDouble.h"
#include "MinusDouble.h"
#include "MultDouble.h"
#include "DivideDouble.h"
#include "AbsoluteDouble.h"
#include "If.h"
#include "LessThan.h"
#include "GreaterThan.h"
#include "Equal.h"
#include "Between.h"

//#include "TempDFunctionP.h"
//#include "TempDFunctionD.h"

#include "Diff.h"

#include "AOI.h"
#include "VOI.h"

#include "ReturnDouble.h"
#include "ReturnBoolean.h"
#include "ReturnInt.h"
#include "ReturnSOperation.h"
#include "ReturnTOperation.h"
#include "ReturnTIndex.h"
#include "ReturnVIndex.h"

#include "ReturnCoordinate.h"
#include "ReturnRect.h"

#include "ClassificationFitness.h"

#include "GPConfig.h"
#include <ctime>

#ifdef MPI_ENABLED
#include "mpi.h"
#endif

// added this
#include <cmath>

#include <sstream>
#include <fstream>
#include "Testing.h"
#include "Data.h"

#include <iostream>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <sstream> // stringstream


#define FILENAME_SIZE 1000

//Default global variables

int imageSize;			//No of attributes per CSV line / No of pixels per image window
int nOfImages;			//No of CSV lines / No of windows to cut out in image
vector<vector<double> > data; // Data to be read from CSV file

vector<double> pixelValues; // Data from CSV line to be tested (shared with terminals/functions)
char *dataClassification;	// Used with testing/training files
ofstream logFile;			// shared for logging purposes
time_t run_time;			// For time logging per generation

typedef vector< vector<Data> > Vector2D; //IMAGE TESTING ONLY
vector<vector<double> > image_data; //IMAGE TESTING ONLY
int imageHeight;		//IMAGE TESTING ONLY
int imageWidth;			//IMAGE TESTING ONLY


//Evolution global variables

int POP_SIZE = 1000;
int INITIAL_POP_SIZE = 0;
int DECIMATION_EVENT = 0;
int MAXDEPTH = 8;
int MINDEPTH = 3;
int EVOLVE = 50;
float MUTATION_RATE = 0.05;
float CROSSOVER_RATE = 0.85;
float ELITISM_RATE = 0.10;
float MUTATION_PROBABILITY = 0.3; //EMO ONLY
bool TARPEIAN = false; // QCS 20121012
bool DDL = false;
bool EMO = false;

int SELECTED_POP = 0;
int WINDOW_SIZE = 30;
int STEP_SIZE = 1;

int DYNAMIC_SELECTION = 0;
int TRAINING = 0; 
int TESTING = 0; 
int POPULATION = 0;
int	IMAGE_TESTING = 0;


int loadConfig(char configFile[FILENAME_SIZE]); // To load in configuration file parameters. Add as necessary.
void loadImage(char dataFile[FILENAME_SIZE]); // loads an PNG file into a 2d pixel array.
void loadData(char dataFile[FILENAME_SIZE]); // reads training/testing data from file
void outputHeatmap(Vector2D &grid, unsigned int imageSize, double max, string origFile); // creates a heatmap if an Image is used;
double findMax(Vector2D &grid); // finds a maximum in a Vector Grid
void outputHeatmapRGB3(Vector2D &grid, unsigned int imageSize, string origFile, unsigned int windowSize, unsigned int shiftSize ); // creates a heatmap for RGB values if an Image is used;










