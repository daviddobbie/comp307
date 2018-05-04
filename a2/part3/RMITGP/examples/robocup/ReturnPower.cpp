/******************************************************************************
 Definition 
 Class:        ReturnPower
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "ReturnPower.h"

//Initialise static data
const int ReturnPower::TYPENUM=2;

ReturnPower::ReturnPower() : ReturnData(), data(0.0)
{
   initTypeNum();
}

ReturnPower::~ReturnPower()
{
}

void ReturnPower::initTypeNum()
{
   setTypeNum(ReturnPower::TYPENUM);
} 

void ReturnPower::setData(double num)
{
   data = num;
}

double ReturnPower::getData() const
{
   return data;
}
