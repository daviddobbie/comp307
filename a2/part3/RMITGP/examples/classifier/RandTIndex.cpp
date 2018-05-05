/******************************************************************************
 Definition file
 Class:        RandTIndex
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

#include "RandTIndex.h"
#include "ReturnTIndex.h"
extern int funWindowSize;

RandTIndex::RandTIndex(GPConfig *conf) :
Terminal(ReturnTIndex::TYPENUM, "tid", conf),
value((int) round(config->randomNumGenerator->randReal()*(pow(2,funWindowSize) - 1)))
{
	while (value==0){
		value = (int) round(config->randomNumGenerator->randReal()*(pow(2,funWindowSize) - 1));
	} 
}

RandTIndex::RandTIndex(int initValue, GPConfig *conf) :
Terminal(ReturnTIndex::TYPENUM, "tid", conf),
value(initValue)
{
}

RandTIndex::~RandTIndex()
{
}

Terminal* RandTIndex::generate(const string &name, GPConfig *conf)
{
	int tmpValue;
	string tmpName("tid");
	char copy[30];
	
	strcpy(copy, name.c_str());
	
	if (name == "")
		return new RandTIndex(conf);
#ifdef OLD_GCC 
	//Older versions of gcc 2.9X shipped with a c++ library which
	//had mistakes in implementation of some methods string::compare 
	//has it's parameters in the wrong order.
	
	else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
	else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
	{	  		
		sscanf(copy, "tid-%d", &tmpValue);
		return new RandTIndex(tmpValue, conf);
	}
	return NULL;      
}

void RandTIndex::evaluate(ReturnData *out)  
{
	if (out->getTypeNum() != (ReturnTIndex::TYPENUM))
		throw string("RandTIndex::evaluate, incorrect ReturnData type");
	
	dynamic_cast<ReturnTIndex *>(out)->setData(value);
}

void RandTIndex::print(string &s)
{
	char str[100];
	sprintf(str, "%s-%d", getName().c_str(),value);
	s.append(str); 
}

Node* RandTIndex::copy()
{
	Node *tmp = new RandTIndex(value, config);
	
	if (tmp == NULL)
		throw string("RandTIndex::copy() Error, out of memory");
	
	return tmp;
}
