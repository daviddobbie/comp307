/******************************************************************************
 Definition 
 Class:        ReturnDummy
 Date created: 02/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "ReturnDummy.h"

const int ReturnDummy::TYPENUM=1;

ReturnDummy::ReturnDummy() : ReturnData()
{
   initTypeNum();
}

ReturnDummy::~ReturnDummy()
{
}

void ReturnDummy::initTypeNum()
{
   setTypeNum(ReturnDummy::TYPENUM);
} 
