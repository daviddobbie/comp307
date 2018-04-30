/******************************************************************************
 Definition 
 Class:        ReturnRect
 
 See header file for details
 ***************************************************************************/

#include "ReturnRect.h"

//Boolean types have a type number of 9
const int ReturnRect::TYPENUM=9;

ReturnRect::ReturnRect() : ReturnData()
{
	initTypeNum();
}

ReturnRect::~ReturnRect()
{
}

void ReturnRect::initTypeNum()
{
	setTypeNum(ReturnRect::TYPENUM);
} 

void ReturnRect::setData(vector<int> r)
{
	data.push_back(r[0]);
	data.push_back(r[1]);
	//data.push_back(r[2]);
}

vector<int> ReturnRect::getData() const
{
	return data;
}
