/******************************************************************************
 Definition file
 Class:        RandInt
 Date created: 21/03/2002
 Written by:   Dylan Mawhinney
 Modified on: 28/03/2006
 Modified by: Djaka W Kurniawan
 
 See header file for details. 
 ***************************************************************************/

#include <cstdio> //for sprintf
#include <string.h>

using namespace std;

#include "GPConfig.h"

#include "RandInt.h"
#include "ReturnInt.h"

RandInt::RandInt(GPConfig *conf) :
Terminal(ReturnInt::TYPENUM, "irand", conf),
value((int)config->randomNumGenerator->randNum())
{
}

RandInt::RandInt(int initValue, GPConfig *conf) :
Terminal(ReturnInt::TYPENUM, "irand", conf),
value(initValue)
{
}

RandInt::~RandInt()
{
}

Terminal* RandInt::generate(const string &name, GPConfig *conf)
{
	int tmpValue;
	string tmpName("irand");
	char copy[20];
	
	strcpy(copy, name.c_str());
	
	if (name == "")
		return new RandInt(conf);
#ifdef OLD_GCC 
	//Older versions of gcc 2.9X shipped with a c++ library which
	//had mistakes in implementation of some methods string::compare 
	//has it's parameters in the wrong order.
	
	else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
		else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
		{
			sscanf(copy, "irand%d", &tmpValue);
			return new RandInt(tmpValue, conf);
		}
	
	return NULL;      
}

void RandInt::evaluate(ReturnData *out)  
{
	if (out->getTypeNum() != (ReturnInt::TYPENUM))
		throw string("RandInt::evaluate, incorrect ReturnData type");
	
	dynamic_cast<ReturnInt *>(out)->setData(value);
}

void RandInt::print(string &s)
{
	char str[100]; 
	
	sprintf(str, "%s%d", getName().c_str(), value);
	s.append(str); 
}

Node* RandInt::copy()
{
	Node *tmp = new RandInt(value, config);
	
	if (tmp == NULL)
		throw string("RandInt::copy() Error, out of memory");
	
	return tmp;
}
