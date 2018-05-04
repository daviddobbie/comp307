/******************************************************************************
 Definition 
 Class:        ReturnBoolean
 Date created: 15/08/2002
 Written by:   Dylan Mawhinney
 
 See header file for details
 ***************************************************************************/

#include "ReturnBoolean.h"

//Boolean types have a type number of 3
const int ReturnBoolean::TYPENUM=3;

ReturnBoolean::ReturnBoolean() : ReturnData(), data(false)
{
	initTypeNum();
}

ReturnBoolean::~ReturnBoolean()
{
}

void ReturnBoolean::initTypeNum()
{
	setTypeNum(ReturnBoolean::TYPENUM);
} 

void ReturnBoolean::setData(bool val)
{
	data = val;
}

bool ReturnBoolean::getData() const
{
	return data;
}
