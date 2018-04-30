/******************************************************************************
 Definition 
 Class:        ReturnVIndex
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 See header file for details
 ***************************************************************************/

#include "ReturnVIndex.h"

//Initialise static data

const int ReturnVIndex::TYPENUM=11;

ReturnVIndex::ReturnVIndex() : ReturnData(), data(0)
{
	initTypeNum();
}

ReturnVIndex::~ReturnVIndex()
{
}

void ReturnVIndex::initTypeNum()
{
	setTypeNum(ReturnVIndex::TYPENUM);
} 

void ReturnVIndex::setData(int num)
{
	data = num;
}

int ReturnVIndex::getData() const
{
	return data;
}
