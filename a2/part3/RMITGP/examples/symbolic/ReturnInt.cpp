/******************************************************************************
 Definition 
 Class:        ReturnInt
 Date created: 19/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "ReturnInt.h"

const int ReturnInt::TYPENUM=1;

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
