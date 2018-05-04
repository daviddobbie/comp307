/******************************************************************************
 Definition file
 Class:        Marker, Flag, Line, Goal
 Date created: 06/09/2002
 Written by:   Dylan Mawhinney

 See header file for details.
******************************************************************************/

#include "Marker.h"

/****************MARKER*******************/

Marker::Marker(string code) : distance(0.0), direction(0.0), timeSeen(0),
                              oldInfo(true), markerCode(code)
{
}

Marker::~Marker()
{

}

void Marker::setMarkerCode(string code)
{
   markerCode = code;
}

string Marker::getMarkerCode() const
{
   return markerCode;
}

void Marker::setDistance(double dist)
{
   distance = dist;
}

void Marker::setDirection(double dir)
{
   direction = dir;
}

double Marker::getDistance() const
{
   return distance;
}

double Marker::getDirection() const
{
   return direction;
}

void Marker::setTimeSeen(int time)
{
   timeSeen = time;
}

int Marker::getTimeSeen() const
{
   return timeSeen;
}
 
void Marker::setOld(bool value)
{
   oldInfo = value;
}

bool Marker::isOld() const  
{
   return oldInfo;
}


/******************* FLAG *********************/

Flag::Flag(string code) : Marker(code), xPos(0.0), yPos(0.0)
{
   if (code.length() == 2)
   {
      if (code[0] == 'l')
         xPos = -52.5;
      else if (code[0] == 'r')
         xPos = 52.5;
      else if (code[0] == 'c')
         xPos = 0.0; 
      else if (code[0] == 't')
         yPos = -34.0;
      else if (code[0] == 'b')
         yPos = 34.0;

      if (code[1] == 't')
         yPos = -34.0;
      else if (code[1] == 'b')
         yPos = 34.0; 
   }
   else if (code.length() == 3)
   {
      if (code[0] == 'p')
      {
         if (code[1] == 'l')
            xPos = -36.0;
         else if (code[1] == 'r')
            xPos = 36.0; 

         if (code[2] == 't') 
            yPos = -20.16;
         else if (code[2] == 'c')
            yPos = 0.0;
         else if (code[2] == 'b')
            yPos = 20.16;
      }     
      else if (code[0] == 'g')
      {
         if (code[1] == 'l')
            xPos = -52.5;
         else if (code[1] == 'r')
            xPos = 52.5;

         if (code[2] == 't')
            yPos = -12.01;
         else if (code[2] == 'b')
            yPos = 12.01;
      }
   }
   else if (code.length() == 4)
   {
      if (code[0] == 't')
      {
         yPos = -39.0;

         if (code[1] == 'l')
         {
            if (code[2] == '1')
               xPos = -10.0;
            else if (code[2] == '2')
               xPos = -20.0;
            else if (code[2] == '3')
               xPos = -30.0;
            else if (code[2] == '4')
               xPos = -40.0;
            else if (code[2] == '5')
               xPos = -50.0;
         }
         else if (code[1] == 'r')
         {
            if (code[2] == '1')
               xPos = 10.0;
            else if (code[2] == '2')
               xPos = 20.0;
            else if (code[2] == '3')
               xPos = 30.0;
            else if (code[2] == '4')
               xPos = 40.0;
            else if (code[2] == '5')
               xPos = 50.0;
         }
      }
      else if (code[0] == 'b')
      {
         yPos = 39.0;

         if (code[1] == 'l')
         {
            if (code[2] == '1')
               xPos = -10.0;
            else if (code[2] == '2')
               xPos = -20.0;
            else if (code[2] == '3')
               xPos = -30.0;
            else if (code[2] == '4')
               xPos = -40.0;
            else if (code[2] == '5')
               xPos = -50.0;
         }
         else if (code[1] == 'r')
         {
            if (code[2] == '1')
               xPos = 10.0;
            else if (code[2] == '2')
               xPos = 20.0;
            else if (code[2] == '3')
               xPos = 30.0;
            else if (code[2] == '4')
               xPos = 40.0;
            else if (code[2] == '5')
               xPos = 50.0;
         }
      }
      else if (code[0] == 'l')
      {
         xPos = -57.5;

         if (code[1] == 't')
         {
            if (code[2] == '1')
               yPos = -10.0;
            else if (code[2] == '2')
               yPos = -20.0;
            else if (code[2] == '3')
               yPos = -30.0;
         }
         else if (code[1] == 'b')
         {
            if (code[2] == '1')
               yPos = 10.0;
            else if (code[2] == '2')
               yPos = 20.0;
            else if (code[2] == '3')
               yPos = 30.0;
         }
      }
      else if (code[0] == 'r')
      {
         xPos = 57.5; 

         if (code[1] == 't')
         {
            if (code[2] == '1')
               yPos = -10.0;
            else if (code[2] == '2')
               yPos = -20.0;
            else if (code[2] == '3')
               yPos = -30.0;
         }
         else if (code[1] == 'b')
         {
            if (code[2] == '1')
               yPos = 10.0;
            else if (code[2] == '2')
               yPos = 20.0;
            else if (code[2] == '3')
               yPos = 30.0;
         }
      }
   }
}

Flag::~Flag()
{
}

void Flag::setXPos(double x)
{
   xPos = x;
}

double Flag::getXPos() const
{
   return xPos;
}

void Flag::setYPos(double y)
{
   yPos = y;
}

double Flag::getYPos() const
{
   return yPos;
}

/*********************LINE*******************/
Line::Line(string code) : Marker(code), sideType(UNDEF)
{
   if (code.length() > 0)
   {
      if (code[0] == 'l')
         sideType = LEFT_LINE;
      else if (code[0] == 'r')
         sideType = RIGHT_LINE;
      else if (code[0] == 't')
         sideType = TOP_LINE;
      else if (code[0] == 'b')
         sideType = BOTTOM_LINE;
   }
}

Line::~Line()
{
}

void Line::setSide(LineType side)
{
   sideType = side;
}

Line::LineType Line::getSide() const
{
   return sideType;
}

/*********************GOAL*****************/

Goal::Goal(string code) : Marker(code), sideType(UNDEF), xPos(0.0), yPos(0.0) 
{
   if(code.length() == 1)
   {
      if (code[0] == 'l')
      {
         sideType = LEFT_GOAL;
         xPos = -52.5;
         yPos = 0.0;
      }
      else if (code[0] == 'r')
      {
         sideType = RIGHT_GOAL;
         xPos = 52.5;
         yPos = 0.0;
      }
   }
}

Goal::~Goal()
{
}

void Goal::setSide(GoalType side)
{
   sideType = side;
}

Goal::GoalType Goal::getSide() const
{
   return sideType;
}

void Goal::setXPos(double x)
{
   xPos = x;
}

double Goal::getXPos() const
{
   return xPos;
}
 
void Goal::setYPos(double y)
{
   yPos = y;
}

double Goal::getYPos() const
{
   return yPos;
}
