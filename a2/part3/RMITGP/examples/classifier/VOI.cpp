/*****************************************************************************
 Definition file
 Class:        VOI 
 Date created: 10/11/2011
 Written by:   Feng Xie
 
 See header file for details
 ******************************************************************************/
#include "VOI.h"
#include "ClassificationFitness.h"
extern int imageSize;
extern vector<double> pixelValues;

VOI::VOI(GPConfig *conf) :
Function(ReturnDouble::TYPENUM, 2, "VOI", conf)
{
	setArgNReturnType(0, ReturnSOperation::TYPENUM);
	setArgNReturnType(1, ReturnVIndex::TYPENUM);
}

VOI::~VOI()
{
}

Function* VOI::generate(const string &name, GPConfig *conf)
{
	
	if (name == "")
		return new VOI(conf);
	else if (name == "VOI")
		return new VOI(conf);
	
	return NULL; 
}

void VOI::evaluate(ReturnData *out)
{
	
	selected_points.clear();
	if (out->getTypeNum() != (ReturnDouble::TYPENUM))
		throw string("VOI::evaluate, incorrect ReturnData type");
	
	for (int i=0; i < maxArgs; i++)
	{
		if (getArgNReturnType(i) != getArgN(i)->getReturnType())
		{
			throw string("VOI::evaluate Error argument has incorrect return type");
		}
	}
	
	ReturnSOperation r1;
	ReturnVIndex r2;
	double result = 0;
	
	getArgN(0)->evaluate(&r1); 
	getArgN(1)->evaluate(&r2);
	
	//cout<<"The function is VOI("<< r1.getData()<<",double)"<<endl;
	
	string selection = itoa(r2.getData(),2);
	int selectionLength = (int)selection.length();
	//if(selectionLength<=imageSize){
		int i;
		//for(i=0;i<selectionLength;i++)
		//{
		//	if(selection[i]=='1')
		//	{
		//		selected_points.push_back(pixelValues[i]);
		//	}
		//}
        for(i=selectionLength-1;i>=0;i--)
        {
            //cout<<"The "<<i<<"th is "<<selection[i]<<endl;
            if(selection[i]=='1')
            {
                selected_points.push_back(pixelValues[imageSize-selectionLength+i]);
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
					result = sqrt((std_sum)/(number_of_picked-1));
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
	//}	
	//cout<<"The result is "<<result<<endl;		
	//selected_points.clear();
	dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* VOI::copy()
{
	int i;
	Function *tmp = new VOI(config);
	
	if (tmp == NULL)
		throw string("VOI::copy() Error, out of memory");
	
	for(i=0; i<getMaxArgs(); i++)
	{ 
		tmp->setArgN(i, getArgN(i)->copy());
	}
	
	return dynamic_cast<Node *>(tmp);
	
}

std::string VOI ::itoa(int value, int base) {
	
	std::string buf;
	
	// check that the base if valid
	if (base < 2 || base > 16) return buf;
	
	enum { kMaxDigits = 35 };
	buf.reserve( kMaxDigits ); // Pre-allocate enough space.
	
	int quotient = value;
	
	// Translating number to string with base:
	do {
		buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
		quotient /= base;
	} while ( quotient );
	
	// Append the negative sign
	if ( value < 0) buf += '-';
	
	std::reverse( buf.begin(), buf.end() );
	return buf;
}