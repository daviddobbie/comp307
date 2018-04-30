/******************************************************************************
 Definition 
 Class:        ReturnCoordinate
 
 See header file for details
 ***************************************************************************/

#include "ReturnCoordinate.h"

//Boolean types have a type number of 8
const int ReturnCoordinate::TYPENUM=8;

ReturnCoordinate::ReturnCoordinate() : ReturnData()
{
	initTypeNum();
}

ReturnCoordinate::~ReturnCoordinate()
{
}

void ReturnCoordinate::initTypeNum()
{
	setTypeNum(ReturnCoordinate::TYPENUM);
} 

void ReturnCoordinate::setData(vector<int> c)
{
	data.push_back(c[0]);
	data.push_back(c[1]);
}

vector<int> ReturnCoordinate::getData() const
{
	return data;
}
