/******************************************************************************
 Definition 
 Class:        ReturnTOperation
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 See header file for details
 ***************************************************************************/

#include "ReturnTOperation.h"

//Initialise static data

const int ReturnTOperation::TYPENUM=5;

ReturnTOperation::ReturnTOperation() : ReturnData(), data(0)
{
	initTypeNum();
}

ReturnTOperation::~ReturnTOperation()
{
}

void ReturnTOperation::initTypeNum()
{
	setTypeNum(ReturnTOperation::TYPENUM);
} 

void ReturnTOperation::setData(int num)
{
	data = num;
}

int ReturnTOperation::getData() const
{
	return data;
}
