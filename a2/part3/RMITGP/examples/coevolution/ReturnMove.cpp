/******************************************************************************
 Definition file
 Class:        ReturnMove
 Date created: 19/09/2002
 Written by:   Dylan Mawhinney

 See header file for details.
***************************************************************************/

#include "ReturnMove.h"

const int ReturnMove::TYPENUM = 1;

const int ReturnMove::UP = 1;
const int ReturnMove::DOWN = 2;
const int ReturnMove::LEFT = 3;
const int ReturnMove::RIGHT = 4;

ReturnMove::ReturnMove() : ReturnData(), moveDirection(UP)
{
   initTypeNum();
}

ReturnMove::~ReturnMove()
{
}

void ReturnMove::initTypeNum() 
{
   setTypeNum(ReturnMove::TYPENUM);
}

void ReturnMove::setData(int data)
{
   moveDirection = data;
}

int ReturnMove::getData() const
{
   return moveDirection;
}
