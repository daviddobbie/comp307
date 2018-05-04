#include<cstring>
#include<cstdlib>
#include <cstdio>
#include <iomanip>

#include "ClassificationFitness.h"
extern vector<double> pixelValues;
extern vector<vector<double> > data;
extern vector<vector<double> > image_data;
extern int maxWindowSize;
extern int imageSize;
extern int imageHeight;
extern int imageWidth;
extern int nOfImages;
extern char *dataClassification;
extern int currentImage;
extern int	IMAGE_TESTING;
extern int WINDOW_SIZE;
/* function prototypes */
//void normal_testing(GeneticProgram *pop[], int popSize);
//void dynamic_selection_testing(GeneticProgram *pop[], int popSize);
//void normal_testing(GeneticProgram *pop[], int popSize);

//void normal_testing(GeneticProgram *pop[], int popSize)
//{
    
//}
char * normal_testing(GeneticProgram *pop)
{
    int totpos = 0;
    int totneg = 0;
    int pospos = 0;
	int posneg = 0;
	int negneg = 0;
	int negpos = 0;
    int rightClassified = 0;
    ReturnDouble rd;
    int k =0;

    string str1;
    char * outputClasses = (char *) malloc (sizeof(char)*(nOfImages+1));
    
    for(k=0; k<nOfImages; k++){
		outputClasses[k]=-1;
	}
    outputClasses[nOfImages] = '\0';
        
    for (int k=0;k<nOfImages; k++)  // Analysis of data file - calculates total positives and negatives
    {
        if(dataClassification[k]=='T')
        {
            totpos++;
        } else {
            totneg++;
        }
    }
    
    for(int imageNum = 0; imageNum < nOfImages; imageNum++)
    {
	//	cout << imageNum << " of " << nOfImages <<endl;	
		pixelValues.clear();
		if (IMAGE_TESTING == 0)
		{
			for(k=0; k < (int)data[imageNum].size(); k++)
			{
				pixelValues.push_back( data[imageNum][k]);
			}
		}
		else
		{
			for(int y=imageNum/(imageHeight-WINDOW_SIZE+1); y < imageNum/(imageHeight-WINDOW_SIZE+1)+WINDOW_SIZE; y++)
			{
				for (int x = imageNum%(imageWidth-WINDOW_SIZE+1);x < imageNum%(imageWidth-WINDOW_SIZE+1)+WINDOW_SIZE; x++)
				{
					pixelValues.push_back( image_data[y][x]);
				}
			}
		}
        int classification = 0;
        
        rd.setData(0);
        pop->evaluate(&rd);
        
 //       if (imageNum>=maxWindowSize-1) {
            
#ifdef WIN32 
            if (!_isnan(rd.getData()))
#else
            if (!isnan(rd.getData()))
#endif
            {
                if (rd.getData() >= 0) {
                    classification = 'T';
                    outputClasses[imageNum] = 'T';
                    
                    if (dataClassification[imageNum] == classification) {
                        rightClassified++;
                        pospos++;
                    } else {
                        posneg++;
                    }
                } else {
                    classification = 'F'; 
                    outputClasses[imageNum] = 'F';
                    
                    if (dataClassification[imageNum] == classification) {
                        rightClassified++;
                        negneg++;
                    } else {
                        negpos++;
                    }
                }
            }
  //      }
    }
    
    float baseFitness = (float)rightClassified/ (nOfImages)* 100.0;
 //   pop->setAccuracy(baseFitness);

	printf("\nAccuracy calculated in new test set: %0.4f%%\n", baseFitness);

    cout << "True Positives: " << pospos<<"/"<<totpos<<" "<<((double)pospos/totpos * 100.0) << "%" << endl;
    cout << "True Negatives: " << negneg<<"/"<<totneg<<" "<<((double)negneg/totneg * 100.0) << "%" << endl;	
    cout << "False Positives: " << posneg<<"/"<<totneg<<" "<<((double)posneg/totneg * 100.0) << "%" << endl;
    cout << "False Negatives: " << negpos<<"/"<<totpos<<" "<<((double)negpos/totpos * 100.0) << "%" << endl;
	
	cout << "\nConfusion Matrix"<<endl;
	cout <<right<<setw(7)<<"a"<<setw(7)<<"b"<<"   << classified as"<<endl;
	cout <<right<<setw(7)<<pospos<<setw(7)<<negpos<<" | a = Positive Result"<<endl;
	cout <<right<<setw(7)<<posneg<<setw(7)<<negneg<<" | b = Negative Result"<<endl;	
    
    return outputClasses;
}



char * dynamic_selection_testing(GeneticProgram *pop)
{
	int j, k;
	string str1;
	int rounded;
	ReturnDouble rd;
	int rightClassified = 0;
	char range[502];
	char * outputClasses = (char *) malloc (sizeof(char)*(nOfImages+1));
	int pospos = 0;
	int posneg = 0;
	int negneg = 0;
	int negpos = 0;
	int totpos, totneg;
	
	totpos = totneg = 0;
	for(k=0; k<nOfImages; k++){
		outputClasses[k]=-1;
	}
	for (k=0; k<nOfImages; k++)
	{
		if(dataClassification[k] == 'T')
		{
			totpos++;
		} else {
			totneg++;
		}
	}
	
	pop->printRange(str1);
	strcpy(range, str1.c_str());
	for (j=0; j<nOfImages; j++)
	{
	//	cout << j << " of " << nOfImages <<endl;	
		pixelValues.clear();
		if (IMAGE_TESTING == 0)
		{
			for(k=0; k < (int)data[j].size(); k++)
			{
				pixelValues.push_back( data[j][k]);
			}
		}
		else
		{
			for(int y=j/(imageHeight-WINDOW_SIZE+1); y < j/(imageHeight-WINDOW_SIZE+1)+WINDOW_SIZE; y++)
			{
				for (int x = j%(imageWidth-WINDOW_SIZE+1);x < j%(imageWidth-WINDOW_SIZE+1)+WINDOW_SIZE; x++)
				{			
					pixelValues.push_back( image_data[y][x]);
				}
			}
		}
		
		pop->evaluate(&rd);
//		if(j>=maxWindowSize-1){
			rounded = (int) round(rd.getData());
			if (rounded < -250)
				rounded = -250;
			if (rounded > 250)
				rounded = 250;
			// Saves the output of the test case into the string
			if (range[rounded+250] == '0') outputClasses[j] = 'F';
			if (range[rounded+250] == '1') outputClasses[j] = 'T';
			outputClasses[nOfImages] = '\0';
			// magic number 48 is to convert the ascii character into the number 0 or 1
			if (dataClassification[j] == 'T') {
				if (dataClassification[j] == outputClasses[j]) {

					rightClassified++;
					pospos++;
				} else {
					negpos++;
				}
			} else {
				if (dataClassification[j] == outputClasses[j]) {

					rightClassified++;
					negneg++;
				} else {
					posneg++;
				}
			}
//		}
	}
    float baseFitness = ((float)pospos/totpos* 50.0+(float)negneg/totneg*50);
 //   pop->setAccuracy(baseFitness);

	printf("\nAccuracy calculated in new test set: %0.4f%%\n", baseFitness);

    cout << "True Positives: " << pospos<<"/"<<totpos<<" "<<((double)pospos/totpos * 100.0) << "%" << endl;
    cout << "True Negatives: " << negneg<<"/"<<totneg<<" "<<((double)negneg/totneg * 100.0) << "%" << endl;	
    cout << "False Positives: " << posneg<<"/"<<totneg<<" "<<((double)posneg/totneg * 100.0) << "%" << endl;
    cout << "False Negatives: " << negpos<<"/"<<totpos<<" "<<((double)negpos/totpos * 100.0) << "%" << endl;
    
	cout << "\nConfusion Matrix"<<endl;
	cout <<right<<setw(7)<<"a"<<setw(7)<<"b"<<"   << classified as"<<endl;
	cout <<right<<setw(7)<<pospos<<setw(7)<<negpos<<" | a = Positive Result"<<endl;
	cout <<right<<setw(7)<<posneg<<setw(7)<<negneg<<" | b = Negative Result"<<endl;	
	
	
	
	return outputClasses;
}


