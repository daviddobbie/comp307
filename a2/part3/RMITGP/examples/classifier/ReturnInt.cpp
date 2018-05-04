/******************************************************************************
 Definition 
 Class:        ReturnInt
 Date created: 20/03/2002
 Written by:   Dylan Mawhinney
 
 See header file for details
 ***************************************************************************/

#include "ReturnInt.h"

//Initialise static data

const int ReturnInt::TYPENUM=4;

ReturnInt::ReturnInt() : ReturnData(), data(0)
{
	initTypeNum();
}

ReturnInt::~ReturnInt()
{
}

void ReturnInt::initTypeNum()
{
	setTypeNum(ReturnInt::TYPENUM);
} 

void ReturnInt::setData(int num)
{
	data = num;
}

int ReturnInt::getData() const
{
	return data;
}
