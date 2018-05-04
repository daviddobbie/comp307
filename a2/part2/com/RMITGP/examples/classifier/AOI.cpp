/*****************************************************************************
 Definition file
 Class:        AOI 
 Date created: 10/11/2011
 Written by:   Feng Xie
 
 See header file for details
 ******************************************************************************/
#include "AOI.h"
#include "ClassificationFitness.h"
extern int imageHeight;
extern int imageWidth;
extern vector<double> pixelValues;

AOI::AOI(GPConfig *conf) :
Function(ReturnDouble::TYPENUM, 3, "AOI", conf)
{
	setArgNReturnType(0, ReturnSOperation::TYPENUM);
	setArgNReturnType(1, ReturnCoordinate::TYPENUM);
	setArgNReturnType(2, ReturnRect::TYPENUM);
}

AOI::~AOI()
{
}

Function* AOI::generate(const string &name, GPConfig *conf)
{
	
	if (name == "")
		return new AOI(conf);
	else if (name == "AOI")
		return new AOI(conf);
	
	return NULL; 
}

void AOI::evaluate(ReturnData *out)
{
	
	selected_points.clear();
	if (out->getTypeNum() != (ReturnDouble::TYPENUM))
		throw string("AOI::evaluate, incorrect ReturnData type");
	
	for (int i=0; i < maxArgs; i++)
	{
		if (getArgNReturnType(i) != getArgN(i)->getReturnType())
		{
			throw string("AOI::evaluate Error argument has incorrect return type");
		}
	}
	
	ReturnSOperation r1;
	ReturnCoordinate r2;
	ReturnRect r3;
	double result = 0;
	
	getArgN(0)->evaluate(&r1); 
	getArgN(1)->evaluate(&r2);
	getArgN(2)->evaluate(&r3);
	
	
	vector<int> c = r2.getData();
	vector<int> r = r3.getData();
	
	int x = c[0];
	int y = c[1];
	int w = r[0];
	int h = r[1];

	
	if(y+h>imageHeight){
		h = imageHeight-y;
	}
	if(x+w>imageWidth){
		w = imageWidth-x;
	}
	
	//cout<<"The function is AOI("<< r1.getData()<<" ["<<x<<","<<y<<
	//"] "<<"["<<w<<","<<h<<"])"<<endl;
	
	int i=0;
	int j=0;
	
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			selected_points.push_back(pixelValues[(i+y)*imageWidth+x+j]);
		}
	}
	
	//cout<<"The data is ";
	//for(int k=0;k<(int)selected_points.size();k++){
	//	cout<<selected_points[k]<<" ";
	//}
	//cout<<endl;
	
	int number_of_picked=(int)selected_points.size();
	
	double avg_sum = 0;
	double avg= 0;
	double std_sum = 0;
	//double std= 0;
	//double skewness_sum = 0;
	int odd = 0;
	
	switch(r1.getData())
	{
		// case MAX:
			// sort(selected_points.begin(),selected_points.end());
			// result = selected_points[number_of_picked-1];
			// break;
		// case MIN:
			// sort(selected_points.begin(),selected_points.end());
			// result = selected_points[0];
			// break;
		case MED:
			sort(selected_points.begin(),selected_points.end());
			odd = number_of_picked%2;
			if(odd == 1)
			{
				result = selected_points[(int)floor(number_of_picked/2)];
			}else
			{
				result = (selected_points[number_of_picked/2-1]+selected_points[number_of_picked/2])/2;
			}						
			break;
		case AVG:
			avg_sum = 0.0;
			for(i=0;i<number_of_picked;i++)
			{
				avg_sum += selected_points[i];
			}
			result = avg_sum/number_of_picked; 			
			break;
		case STD:
			if (number_of_picked < 2)
			{
				result = 0;
			}else
			{
				avg_sum = 0.0;
				for(i=0;i<number_of_picked;i++)
				{
					avg_sum += selected_points[i];
				}
				avg = avg_sum/number_of_picked;
				
				std_sum = 0.0;
				for(i=0;i<number_of_picked;i++)
				{
					std_sum += (selected_points[i]-avg)*(selected_points[i]-avg);
				}
				result = sqrt((std_sum))/(number_of_picked-1);
			}			
			break;
		case RANGE:
			sort(selected_points.begin(),selected_points.end());
			result = selected_points[number_of_picked-1]-selected_points[0];
			break;
			//case SKEWNESS:
			//	avg_sum = 0.0;
			//	for(i=0;i<number_of_picked;i++)
			//	{
			//		avg_sum += selected_points[i];
			//	}
			//	avg = avg_sum/number_of_picked;
			
			//	std_sum = 0.0;
			//	for(i=0;i<number_of_picked;i++)
			//	{
			//		std_sum += (selected_points[i]-avg)*(selected_points[i]-avg);
			//	}
			//	if (std_sum==0) {
			//		value = 0;
			//	}else {
			//		std = sqrt(std_sum)/(number_of_picked-1);				
			//		skewness_sum = 0.0;
			//		for(i=0;i<number_of_picked;i++)
			//		{
			//			skewness_sum += (selected_points[i]-avg)*(selected_points[i]-avg)*(selected_points[i]-avg)*(selected_points[i]-avg)/std/std/std/std;
			//		}
			//		value = skewness_sum/number_of_picked-3;
			//	}				
			//	break;
		default:
			result = 0.0;
			break;
	}	
	//cout<<"The result is "<<result<<endl;		
	//selected_points.clear();
	dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* AOI::copy()
{
	int i;
	Function *tmp = new AOI(config);
	
	if (tmp == NULL)
		throw string("AOI::copy() Error, out of memory");
	
	for(i=0; i<getMaxArgs(); i++)
	{ 
		tmp->setArgN(i, getArgN(i)->copy());
	}
	
	return dynamic_cast<Node *>(tmp);
	
}
