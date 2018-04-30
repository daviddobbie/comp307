/******************************************************************************
 Definition file
 Class:        Coordinate
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 See header file for details. 
 ***************************************************************************/
using namespace std;
#include <cstdio> //for sprintf
#include <string.h>
#include <iostream>
#include <math.h>
#include "GPConfig.h"

#include "Coordinate.h"
#include "ReturnCoordinate.h"
extern int imageHeight;
extern int imageWidth;

Coordinate::Coordinate(GPConfig *conf) :
Terminal(ReturnCoordinate::TYPENUM, "c", conf)
{
	x=(int) round(config->randomNumGenerator->randReal()*(imageWidth - 1));
	y=(int) round(config->randomNumGenerator->randReal()*(imageHeight - 1));
	while (x==imageWidth-1) {
		x = x-1;
	}
	while (y==imageHeight-1) {
		y = y-1;
	}
	value.push_back(x);
	value.push_back(y);
}

Coordinate::Coordinate(int xp,int yp, GPConfig *conf) :
Terminal(ReturnCoordinate::TYPENUM, "c", conf),
x(xp),y(yp)
{
	value.push_back(x);
	value.push_back(y);
}

Coordinate::~Coordinate()
{
}

Terminal* Coordinate::generate(const string &name, GPConfig *conf)
{
	int tmpValue1;
	int tmpValue2;
	string tmpName("c");
	char copy[30];
	
	strcpy(copy, name.c_str());
	
	if (name == "")
		return new Coordinate(conf);
#ifdef OLD_GCC 
	//Older versions of gcc 2.9X shipped with a c++ library which
	//had mistakes in implementation of some methods string::compare 
	//has it's parameters in the wrong order.
	
	else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
	else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
	{	  		
		sscanf(copy, "c[%d,%d]", &tmpValue1,&tmpValue2);
		return new Coordinate(tmpValue1,tmpValue2,conf);
	}
	return NULL;      
}

void Coordinate::evaluate(ReturnData *out)  
{
	if (out->getTypeNum() != (ReturnCoordinate::TYPENUM))
		throw string("Coordinate::evaluate, incorrect ReturnData type");
	
	dynamic_cast<ReturnCoordinate *>(out)->setData(value);
}

void Coordinate::print(string &s)
{
	char str[100];
	sprintf(str, "%s[%d,%d]", getName().c_str(),x,y);
	s.append(str); 
}

Node* Coordinate::copy()
{
	Node *tmp = new Coordinate(x,y,config);
	
	if (tmp == NULL)
		throw string("Coordinate::copy() Error, out of memory");
	
	return tmp;
}
