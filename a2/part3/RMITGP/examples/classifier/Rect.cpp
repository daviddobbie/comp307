/******************************************************************************
 Definition file
 Class:        Rect
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 See header file for details. 
 ***************************************************************************/
using namespace std;
#include <cstdio> //for sprintf
#include <string.h>
#include <math.h>
#include <iostream>
#include "GPConfig.h"

#include "Rect.h"
#include "ReturnRect.h"
extern int imageHeight;
extern int imageWidth;

Rect::Rect(GPConfig *conf) :
Terminal(ReturnRect::TYPENUM, "rect", conf)
{
	

	w=(int) round(config->randomNumGenerator->randReal()*(imageWidth - 1));
	h=(int) round(config->randomNumGenerator->randReal()*(imageHeight - 1));
	if (w==0) {
		w= w+1;
		
	}
	if (h==0) {
		h= h+1;
	}

	value.push_back(w);
	value.push_back(h);


}

Rect::Rect(int wp,int hp, GPConfig *conf) :
Terminal(ReturnRect::TYPENUM, "rect", conf),
w(wp),h(hp)
{
	value.push_back(w);
	value.push_back(h);
}

Rect::~Rect()
{
}

Terminal* Rect::generate(const string &name, GPConfig *conf)
{

	int tmpValue1;
	int tmpValue2;

	string tmpName("rect");
	char copy[30];
	
	strcpy(copy, name.c_str());
	
	if (name == "")
		return new Rect(conf);
#ifdef OLD_GCC 
	//Older versions of gcc 2.9X shipped with a c++ library which
	//had mistakes in implementation of some methods string::compare 
	//has it's parameters in the wrong order.
	
	else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
	else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
	{	  		
		sscanf(copy, "rect[%d,%d]", &tmpValue1,&tmpValue2);
		return new Rect(tmpValue1,tmpValue2,conf);
	}
	return NULL;      
}

void Rect::evaluate(ReturnData *out)  
{
	if (out->getTypeNum() != (ReturnRect::TYPENUM))
		throw string("Rect::evaluate, incorrect ReturnData type");
	
	dynamic_cast<ReturnRect *>(out)->setData(value);
}

void Rect::print(string &s)
{
	char str[100];
	sprintf(str, "%s[%d,%d]", getName().c_str(),w,h);
	s.append(str); 
}

Node* Rect::copy()
{
	Node *tmp = new Rect(w,h,config);
	
	if (tmp == NULL)
		throw string("Rect::copy() Error, out of memory");
	
	return tmp;
}
