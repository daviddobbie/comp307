/******************************************************************************
 Definition 
 Class:        ReturnAngle
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "ReturnAngle.h"

//Initialise static data
const int ReturnAngle::TYPENUM=3;

ReturnAngle::ReturnAngle() : ReturnData(), data(0.0)
{
   initTypeNum();
}

ReturnAngle::~ReturnAngle()
{
}

void ReturnAngle::initTypeNum()
{
   setTypeNum(ReturnAngle::TYPENUM);
} 

void ReturnAngle::setData(double num)
{
   data = num;
}

double ReturnAngle::getData() const
{
   return data;
}
