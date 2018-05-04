/******************************************************************************
 Definition file
 Class:        GreaterThan 
 Date created: 16/08/2002
 Written by:   Dylan Mawhinney
 Modified on: 28/03/2006
 Modified by: Djaka W Kurniawan
 
 See header file for details
 ******************************************************************************/

#include <string>

using namespace std;

#include "GreaterThan.h"
#include "ReturnDouble.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

GreaterThan::GreaterThan(GPConfig *conf):Function(ReturnBoolean::TYPENUM, 2, "d>=", conf)
{
	setArgNReturnType(0, ReturnDouble::TYPENUM); 
	setArgNReturnType(1, ReturnDouble::TYPENUM);
}

GreaterThan::~GreaterThan()
{
}

Function* GreaterThan::generate(const string &name, GPConfig *conf)
{
	if (name == "")
		return new GreaterThan(conf);
	else if (name == "d>=")
		return new GreaterThan(conf);
	
	return NULL;     
}

void GreaterThan::evaluate(ReturnData *out)
{
	if (out->getTypeNum() != ReturnBoolean::TYPENUM)
		throw string("GreaterThan::evaluate, incorrect ReturnData type");
	
	for (int i=0; i < maxArgs; i++)
	{
		if (getArgNReturnType(i) != getArgN(i)->getReturnType())
		{
			throw string("GreaterThan::evaluate Error argument has incorrect return type");
		}
	}
	
	ReturnDouble r1;
	ReturnDouble r2;
	bool result;
	
	getArgN(0)->evaluate(&r1); 
	getArgN(1)->evaluate(&r2); 
	
	result = r1.getData() >= r2.getData();
	
	dynamic_cast<ReturnBoolean *>(out)->setData(result); 
}

Node* GreaterThan::copy()
{
	int i;
	Function *tmp = new GreaterThan(config);
	
	if (tmp == NULL)
		throw string("GreaterThan::copy() Error, out of memory");
	
	for(i=0; i<getMaxArgs(); i++)
	{ 
		tmp->setArgN(i, getArgN(i)->copy());
	}
	
	return dynamic_cast<Node *>(tmp);
}
