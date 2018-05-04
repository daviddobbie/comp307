/******************************************************************************
 Definition 
 Class:        ReturnTIndex
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 See header file for details
 ***************************************************************************/

#include "ReturnTIndex.h"

//Initialise static data

const int ReturnTIndex::TYPENUM=6;

ReturnTIndex::ReturnTIndex() : ReturnData(), data(0)
{
	initTypeNum();
}

ReturnTIndex::~ReturnTIndex()
{
}

void ReturnTIndex::initTypeNum()
{
	setTypeNum(ReturnTIndex::TYPENUM);
} 

void ReturnTIndex::setData(int num)
{
	data = num;
}

int ReturnTIndex::getData() const
{
	return data;
}
