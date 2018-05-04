/******************************************************************************
 Definition file
 Class:        Attribute
 Date created: 12/04/2006
 Written by: Djaka W Kurniawan
 
 See header file for details. 
 ***************************************************************************/

#include <cstdio> //for sprintf
#include <string.h>
#include <math.h>

using namespace std;

#include "GPConfig.h"

#include "Attribute.h"
#include "ReturnDouble.h"

extern int imageSize;
extern vector<double> pixelValues;

Attribute::Attribute(GPConfig *conf) :
Terminal(ReturnDouble::TYPENUM, "Att", conf),
pixel((int) round(config->randomNumGenerator->randReal()*((imageSize) - 1)))
{
	value =0.0;
}

Attribute::Attribute(int initValue, GPConfig *conf) :
Terminal(ReturnDouble::TYPENUM, "Att", conf),
pixel(initValue)
{
}

Attribute::Attribute(double initValue, GPConfig *conf) :
Terminal(ReturnDouble::TYPENUM, "Att", conf),
value(initValue)
{
}

Attribute::~Attribute()
{
}

Terminal* Attribute::generate(const string &name, GPConfig *conf)
{
	int tmpValue;
	string tmpName("Att");
	char copy[20];
	
	strcpy(copy, name.c_str());
	
	if (name == "")
		return new Attribute(conf);
#ifdef OLD_GCC 
	//Older versions of gcc 2.9X shipped with a c++ library which
	//had mistakes in implementation of some methods string::compare 
	//has it's parameters in the wrong order.
	else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
		else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
		{
			sscanf(copy, "Att%d", &tmpValue);
			return new Attribute(tmpValue, conf);
		}
	
	return NULL;      
}

void Attribute::evaluate(ReturnData *out)  
{
	if (out->getTypeNum() != (ReturnDouble::TYPENUM))
		throw string("Attribute::evaluate, incorrect ReturnData type");
	
	value = 0;
	if( pixel < (int)pixelValues.size())
		value = pixelValues[pixel]; 
	dynamic_cast<ReturnDouble *>(out)->setData(value);
}

void Attribute::print(string &s)
{
	char str[100]; 
	
	sprintf(str, "%s%d", getName().c_str(), pixel);
	s.append(str); 
}

Node* Attribute::copy()
{
	Node *tmp = new Attribute(pixel, config);
	
	if (tmp == NULL)
		throw string("Attribute::copy() Error, out of memory");
	
	return tmp;
}
