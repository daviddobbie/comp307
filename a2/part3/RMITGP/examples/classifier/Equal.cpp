/*****************************************************************************
 Definition file
 Class:        Equal 
 Date created: 28/03/2006
 Written by:   Djaka W Kurniawan
 
 See header file for details
 *****************************************************************************/

#include <string>

using namespace std;

#include "Equal.h"
#include "ReturnDouble.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

Equal::Equal(GPConfig *conf): Function(ReturnBoolean::TYPENUM, 2, "d=", conf)
{
	setArgNReturnType(0, ReturnDouble::TYPENUM); 
	setArgNReturnType(1, ReturnDouble::TYPENUM);
}

Equal::~Equal()
{
	
}

Function* Equal::generate(const string &name, GPConfig *conf)
{
	if (name == "")
		return new Equal(conf);
	else if (name == "d=")
		return new Equal(conf);
	
	return NULL;     
}

void Equal::evaluate(ReturnData *out)
{
	if (out->getTypeNum() != ReturnBoolean::TYPENUM)
		throw string("Equal::evaluate, incorrect ReturnData type");
	
	for (int i=0; i < maxArgs; i++)
	{
		if (getArgNReturnType(i) != getArgN(i)->getReturnType())
		{
			throw string("Equal::evaluate Error argument has incorrect return type");
		}
	}
	
	ReturnDouble r1;
	ReturnDouble r2;
	bool result;
	
	getArgN(0)->evaluate(&r1); 
	getArgN(1)->evaluate(&r2); 
	
	result = r1.getData() == r2.getData();
	
	dynamic_cast<ReturnBoolean *>(out)->setData(result); 
}

Node* Equal::copy()
{
	int i;
	Function *tmp = new Equal(config);
	
	if (tmp == NULL)
		throw string("Equal::copy() Error, out of memory");
	
	for(i=0; i<getMaxArgs(); i++)
	{ 
		tmp->setArgN(i, getArgN(i)->copy());
	}
	
	return dynamic_cast<Node *>(tmp);
}
