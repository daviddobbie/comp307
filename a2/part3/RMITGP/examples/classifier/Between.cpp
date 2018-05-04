/*****************************************************************************
 Definition file
 Class:        Between 
 Date created: 28/03/2006
 Written by:   Djaka W Kurniawan
 
 See header file for details
 *****************************************************************************/

#include <string>

using namespace std;

#include "Between.h"
#include "ReturnDouble.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

Between::Between(GPConfig *conf) : Function(ReturnBoolean::TYPENUM, 3, "between", conf)
{
	setArgNReturnType(0, ReturnDouble::TYPENUM);  //first, 
	setArgNReturnType(1, ReturnDouble::TYPENUM);  //second and third 
	setArgNReturnType(2, ReturnDouble::TYPENUM);  //doubles 
}

Between::~Between()
{
	
}

Function* Between::generate(const string &name, GPConfig *conf)
{
	if (name == "")
		return new Between(conf);
	else if (name == "between")
		return new Between(conf);
	
	return NULL;     
}

void Between::evaluate(ReturnData *out)
{
	if (out->getTypeNum() != ReturnBoolean::TYPENUM)
		throw string("Between::evaluate, incorrect ReturnData type");
	
	for (int i=0; i < maxArgs; i++)
	{
		if (getArgNReturnType(i) != getArgN(i)->getReturnType())
		{
			throw string("Between::evaluate Error argument has incorrect return type");
		}
	}
	
	ReturnDouble r1;
	ReturnDouble r2;
	ReturnDouble r3;
	bool result;
	
	getArgN(0)->evaluate(&r1); 
	getArgN(1)->evaluate(&r2); 
	getArgN(2)->evaluate(&r3); 
	
	result = (r2.getData() <= r1.getData()) && (r1.getData() <= r3.getData());
	dynamic_cast<ReturnBoolean *>(out)->setData(result); 
}

Node* Between::copy()
{
	int i;
	Function *tmp = new Between(config);
	
	if (tmp == NULL)
		throw string("Between::copy() Error, out of memory");
	
	for(i=0; i<getMaxArgs(); i++)
	{ 
		tmp->setArgN(i, getArgN(i)->copy());
	}
	
	return dynamic_cast<Node *>(tmp);
}
