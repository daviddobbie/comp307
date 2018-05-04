/******************************************************************************
 Definition file
 Class:        RandSOperation
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 See header file for details. 
 ***************************************************************************/

#include <cstdio> //for sprintf
#include <string.h>
#include <iostream>
using namespace std;
#include <math.h>
#include "GPConfig.h"

#include "RandSOperation.h"
#include "ReturnSOperation.h"

RandSOperation::RandSOperation(GPConfig *conf) :
Terminal(ReturnSOperation::TYPENUM, "soper", conf),
value((int) round(config->randomNumGenerator->randReal()*((OPER_END) - 1)))
{
}

RandSOperation::RandSOperation(int initValue, GPConfig *conf) :
Terminal(ReturnSOperation::TYPENUM, "soper", conf),
value(initValue)
{
}

RandSOperation::~RandSOperation()
{
}

Terminal* RandSOperation::generate(const string &name, GPConfig *conf)
{
	char* tmpChars = new char[15];
	int tmpValue;
	string tmpName("soper");
	char copy[30];
	
	strcpy(copy, name.c_str());
	
	if (name == "")
		return new RandSOperation(conf);
#ifdef OLD_GCC 
	//Older versions of gcc 2.9X shipped with a c++ library which
	//had mistakes in implementation of some methods string::compare 
	//has it's parameters in the wrong order.
	
	else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
	else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
	{	  
		vector<string> soper_strings;
		//soper_strings.push_back("MAX");
		//soper_strings.push_back("MIN");
		soper_strings.push_back("MED");
		soper_strings.push_back("AVG");
		soper_strings.push_back("STD");
		soper_strings.push_back("RAN");
		//soper_strings.push_back("SKEWNESS");
		
		sscanf(copy, "soper-%s", tmpChars);
		string tmpString(tmpChars);
		for (int i = 0; i < OPER_END; i++)
		{
#ifdef OLD_GCC 
			if (tmpString.compare(soper_strings.at(i), 0,soper_strings.at(i).size()) == 0)
#else
			if (tmpString.compare(0,soper_strings.at(i).size(), soper_strings.at(i)) == 0)
#endif
			{
				tmpValue = i;
			}
		}		
		delete [] tmpChars;
		return new RandSOperation(tmpValue, conf);
	}
	
	return NULL;      
}

void RandSOperation::evaluate(ReturnData *out)  
{
	if (out->getTypeNum() != (ReturnSOperation::TYPENUM))
		throw string("RandSOperation::evaluate, incorrect ReturnData type");
	
	dynamic_cast<ReturnSOperation *>(out)->setData(value);
}

void RandSOperation::print(string &s)
{
	char str[100];
	string soper;
	switch(value)
	{
		//case MAX: 
			//soper = "MAX";
			// break;
		// case MIN: 
			// soper = "MIN";
			// break;
		case MED: 
			soper = "MED";
			break;
		case AVG: 
			soper = "AVG";
			break;
		case STD: 
			soper = "STD";
			break;
		case RANGE: 
			soper = "RAN";
			break;
		//case SKEWNESS: 
		//	soper = "SKEWNESS";
		//	break;	
	}
	char* soperChars = new char[soper.length()+1];
	strcpy(soperChars, soper.c_str());
	sprintf(str, "%s-%s", getName().c_str(),soperChars);
	s.append(str); 
	delete [] soperChars;
}

Node* RandSOperation::copy()
{
	Node *tmp = new RandSOperation(value, config);
	
	if (tmp == NULL)
		throw string("RandSOperation::copy() Error, out of memory");
	
	return tmp;
}
