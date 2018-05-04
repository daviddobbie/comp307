/*****************************************************************************
 Definition file
 Class:        Diff 
 Date created: 10/11/2011
 Written by:   Feng Xie
 
 See header file for details
 ******************************************************************************/
#include "Diff.h"
#include "ClassificationFitness.h"

Diff::Diff(GPConfig *conf) :
Function(ReturnDouble::TYPENUM, 1, "dDiff", conf)
{
	setArgNReturnType(0, ReturnDouble::TYPENUM);
	last_value = 0;
	first = true;
}

Diff::~Diff()
{
}

Function* Diff::generate(const string &name, GPConfig *conf)
{
	if (name == "")
		return new Diff(conf);
	else if (name == "dDiff")
		return new Diff(conf);
	
	return NULL; 
}

void Diff::evaluate(ReturnData *out)
{
	
	if (out->getTypeNum() != (ReturnDouble::TYPENUM))
		throw string("Diff::evaluate, incorrect ReturnData type");
	
	for (int i=0; i < maxArgs; i++)
	{
		if (getArgNReturnType(i) != getArgN(i)->getReturnType())
		{
			throw string("Diff::evaluate Error argument has incorrect return type");
		}
	}
	
	ReturnDouble r1;
	double result = 0;
	
	getArgN(0)->evaluate(&r1); 
	
	//cout<<"The function is dDiff("<< r1.getData()<<")"<<endl;
	
	if (first) {
		//cout<<"There is no last value."<<endl;
		first = false;
	}else {
		//cout<<"The last_value data is "<< last_value<<endl;	
		result = r1.getData()-last_value;
	}
	
	last_value = r1.getData();
		
	//cout<<"The result is "<<result<<endl;		
	dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* Diff::copy()
{
	int i;
	Function *tmp = new Diff(config);
	
	if (tmp == NULL)
		throw string("Diff::copy() Error, out of memory");
	
	for(i=0; i<getMaxArgs(); i++)
	{ 
		tmp->setArgN(i, getArgN(i)->copy());
	}
	
	return dynamic_cast<Node *>(tmp);
	
}


