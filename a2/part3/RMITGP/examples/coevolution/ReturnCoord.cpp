/******************************************************************************
 Definition 
 Class:        ReturnCoord
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "ReturnCoord.h"

const int ReturnCoord::TYPENUM = 2;

ReturnCoord::ReturnCoord() : ReturnData(), data(0)
{
   initTypeNum();
}

ReturnCoord::~ReturnCoord()
{
}

void ReturnCoord::initTypeNum()
{
   setTypeNum(ReturnCoord::TYPENUM);
} 

void ReturnCoord::setData(int num)
{
   data = num;
}

int ReturnCoord::getData() const
{
   return data;
}
