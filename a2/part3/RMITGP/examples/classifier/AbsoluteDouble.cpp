/*****************************************************************************
 Definition file
 Class:        AbsoluteDouble 
 
 See header file for details
 ******************************************************************************/

#include <string>

using namespace std;

#include "AbsoluteDouble.h"
#include "ReturnDouble.h"

#include <float.h>
#include <math.h>

AbsoluteDouble::AbsoluteDouble(GPConfig *conf):Function(ReturnDouble::TYPENUM, 1, "abs", conf)
{
	for (int i=0; i < maxArgs; i++)
	{
		setArgNReturnType(i, ReturnDouble::TYPENUM);   
	}
}

AbsoluteDouble::~AbsoluteDouble()
{
}

Function* AbsoluteDouble::generate(const string &name, GPConfig *conf)
{
	if (name == "")
		return new AbsoluteDouble(conf);
	else if (name == "abs")
		return new AbsoluteDouble(conf);
	
	return NULL;     
}

void AbsoluteDouble::evaluate(ReturnData *out)
{
	if (out->getTypeNum() != ReturnDouble::TYPENUM)
		throw string("AbsoluteDouble::evaluate, incorrect ReturnData type");
	
	for (int i=0; i < maxArgs; i++)
	{
		if (getArgNReturnType(i) != getArgN(i)->getReturnType())
		{
			throw string("AbsoluteDouble::evaluate Error argument has incorrect return type");
		}
	}
	
	ReturnDouble r1;
	
	getArgN(0)->evaluate(&r1); 
	
	double result= fabs(r1.getData());
	dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* AbsoluteDouble::copy()
{
	int i;
	Function *tmp = new AbsoluteDouble(config);
	
	if (tmp == NULL)
		throw string("AbsoluteDouble::copy() Error, out of memory");
	
	for(i=0; i<getMaxArgs(); i++)
	{ 
		tmp->setArgN(i, getArgN(i)->copy());
	}
	
	return dynamic_cast<Node *>(tmp);
}
