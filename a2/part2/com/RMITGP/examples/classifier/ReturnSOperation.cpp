/******************************************************************************
 Definition 
 Class:        ReturnSOperation
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 See header file for details
 ***************************************************************************/

#include "ReturnSOperation.h"

//Initialise static data

const int ReturnSOperation::TYPENUM=10;

ReturnSOperation::ReturnSOperation() : ReturnData(), data(0)
{
	initTypeNum();
}

ReturnSOperation::~ReturnSOperation()
{
}

void ReturnSOperation::initTypeNum()
{
	setTypeNum(ReturnSOperation::TYPENUM);
} 

void ReturnSOperation::setData(int num)
{
	data = num;
}

int ReturnSOperation::getData() const
{
	return data;
}
