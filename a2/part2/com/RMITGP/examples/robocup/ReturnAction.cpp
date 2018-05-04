/******************************************************************************
 Definition 
 Class:        ReturnAction
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "ReturnAction.h"

#include <cstdio>

//Initialise static data
const int ReturnAction::TYPENUM=1;

ReturnAction::ReturnAction() : ReturnData(), numActions(0)
{
   initTypeNum();
}

ReturnAction::~ReturnAction()
{
}

void ReturnAction::initTypeNum()
{
   setTypeNum(ReturnAction::TYPENUM);
} 

void ReturnAction::makeString(ActionType *act, string &actionString)
{
   char actStr[100];

   switch(act->actionType)
   {
      case KICK:
         sprintf(actStr, "(kick %lf %lf)", act->firstParam, act->secondParam);
         break;
      case DASH:
         sprintf(actStr, "(dash %lf)", act->firstParam);
         break;
      case TURN:
         sprintf(actStr, "(turn %lf)", act->firstParam);
         break;
      default:
         break;
   }

   actionString = actStr;
}

void ReturnAction::addKick(double power, double angle)
{
   if (!this->full())
   {
      actionList[numActions].actionType = KICK;
      actionList[numActions].firstParam = power;
      actionList[numActions].secondParam = angle;
      numActions++;
   }
}

void ReturnAction::addDash(double power)
{
   if (!this->full())
   {
      actionList[numActions].actionType = DASH;
      actionList[numActions].firstParam = power;
      numActions++;
   }
}

void ReturnAction::addTurn(double power)
{
   if (!this->full())
   {
      actionList[numActions].actionType = TURN;
      actionList[numActions].firstParam = power;
      numActions++;
   }
}

void ReturnAction::getNextAction(string &actionString)
{
   int i;

   makeString(&(actionList[0]), actionString);   

   for(i=1; i<numActions; i++)
   {
      actionList[i-1] = actionList[i];    
   }

   numActions--;
}
   
void ReturnAction::peekNextAction(string &actionString)
{
   makeString(&(actionList[0]), actionString);   
}

bool ReturnAction::full()
{
   return (numActions >= MAX_ACTIONS);
}

bool ReturnAction::empty()
{
   return (numActions <= 0);
}


