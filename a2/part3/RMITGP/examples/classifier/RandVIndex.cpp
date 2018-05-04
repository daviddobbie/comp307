/******************************************************************************
 Definition file
 Class:        RandVIndex
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

#include "RandVIndex.h"
#include "ReturnVIndex.h"
extern int funWindowSize;
extern int imageSize;

RandVIndex::RandVIndex(GPConfig *conf) :
Terminal(ReturnVIndex::TYPENUM, "vid", conf),
value((int) round(config->randomNumGenerator->randReal()*((pow(2,imageSize) - 1))))
{
	while (value==0){
		value = (int) round(config->randomNumGenerator->randReal()*(pow(2,imageSize) - 1));
	} 
}

RandVIndex::RandVIndex(int initValue, GPConfig *conf) :
Terminal(ReturnVIndex::TYPENUM, "vid", conf),
value(initValue)
{
}

RandVIndex::~RandVIndex()
{
}

Terminal* RandVIndex::generate(const string &name, GPConfig *conf)
{
	int tmpValue;
	string tmpName("vid");
	char copy[30];
	
	strcpy(copy, name.c_str());
	
	if (name == "")
		return new RandVIndex(conf);
#ifdef OLD_GCC 
	//Older versions of gcc 2.9X shipped with a c++ library which
	//had mistakes in implementation of some methods string::compare 
	//has it's parameters in the wrong order.
	
	else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
	else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
	{	  		
		sscanf(copy, "vid-%d", &tmpValue);
		return new RandVIndex(tmpValue, conf);
	}
	return NULL;      
}

void RandVIndex::evaluate(ReturnData *out)  
{
	if (out->getTypeNum() != (ReturnVIndex::TYPENUM))
		throw string("RandVIndex::evaluate, incorrect ReturnData type");
	
	dynamic_cast<ReturnVIndex *>(out)->setData(value);
}

void RandVIndex::print(string &s)
{
	char str[100];
	sprintf(str, "%s-%d", getName().c_str(),value);
	s.append(str); 
}

Node* RandVIndex::copy()
{
	Node *tmp = new RandVIndex(value, config);
	
	if (tmp == NULL)
		throw string("RandVIndex::copy() Error, out of memory");
	
	return tmp;
}
