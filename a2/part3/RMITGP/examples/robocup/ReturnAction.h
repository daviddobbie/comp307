#ifndef _RETURNACTION_H_
#define _RETURNACTION_H_

/******************************************************************************
 Header file
 Class:        ReturnAction
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 ReturnAction is a derived class of ReturnData, it represents an action
 list to be executed by a soccer playing softbot. Actions can be one of
 dash, kick, or turn.
***************************************************************************/

#include "ReturnData.h"

#include <string>

#define MAX_ACTIONS 10

class ReturnAction : public ReturnData
{
   private:
      //Constants to identity the different actions

      static const int KICK = 1;
      static const int DASH = 2;
      static const int TURN = 3;

      //A struct to represent an action
      typedef struct action_s
      {
         int actionType;
         double firstParam;
         double secondParam;
      } ActionType;

      //A list of actions to be executed later
      ActionType actionList[MAX_ACTIONS];
      int numActions;

      void makeString(ActionType *act, std::string &actionString);

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. 
      ************************************************/ 
      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      ReturnAction();
      virtual ~ReturnAction();

      void addKick(double power, double angle);
      void addDash(double power);
      void addTurn(double power);

      void getNextAction(string &actionString); 
      void peekNextAction(string &actionString);

      bool full();
      bool empty();
   protected:

};

#endif
