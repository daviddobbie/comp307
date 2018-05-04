/******************************************************************************
 Definition file
 Class:        MovableObject
 Date created: 06/09/2002
 Written by:   Dylan Mawhinney

 See header file for details.
******************************************************************************/

#include "MovableObject.h"      

MovableObject::MovableObject() : distance(0.0), direction(0.0),
                  changeInDistance(0.0), changeInDirection(0.0),
                  approxXPos(0.0), approxYPos(0.0),
                  timeSeen(0), oldInfo(true)
{
}

MovableObject::~MovableObject()
{
}

void MovableObject::setDistance(double dist)
{
   distance = dist;
}

void MovableObject::setDirection(double dir)
{
   direction = dir;
}

double MovableObject::getDistance() const
{
   return distance;
}

double MovableObject::getDirection() const
{
   return direction;
}

void MovableObject::setChangeInDistance(double dist)
{
   changeInDistance = dist;
}

void MovableObject::setChangeInDirection(double dir)
{
   changeInDirection = dir;
}

double MovableObject::getChangeInDistance() const
{
   return changeInDistance;
}

double MovableObject::getChangeInDirection() const
{
   return changeInDirection;
}

void MovableObject::setApproxXPos(double x)
{
   approxXPos = x;
}

void MovableObject::setApproxYPos(double y)
{
   approxYPos = y;
}

double MovableObject::getApproxXPos() const
{
   return approxXPos;
}

double MovableObject::setApproxYPos() const
{
   return approxYPos;
}

void MovableObject::setTimeSeen(int time)
{
   timeSeen = time;
}

int MovableObject::getTimeSeen() const
{
   return timeSeen;
}
 
void MovableObject::setOld(bool value)
{
   oldInfo = value;
}

bool MovableObject::isOld() const  
{
   return oldInfo;
}

/******************PLAYEROBJECT******************/
PlayerObject::PlayerObject() : uniformNumber(0), sideType(UNDEF)
{
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::setUniformNumber(int num)
{
   uniformNumber = num;
}

int PlayerObject::getUniformNumber() const
{
   return uniformNumber;
}

void PlayerObject::setSide(SideType side)
{
   sideType = side;
}

PlayerObject::SideType PlayerObject::getSide() const
{
   return sideType;
}

void PlayerObject::setGoalie(bool val)
{
   goalie = val;
}

bool PlayerObject::isGoalie() const
{
   return goalie;
}
