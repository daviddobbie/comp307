#ifndef _RETURNMOVE_H_
#define _RETURNMOVE_H_

/******************************************************************************
 Header file
 Class:        ReturnMove
 Date created: 19/09/2002
 Written by:   Dylan Mawhinney

 ReturnMove is a return data class which stores a move made by a player
 in the predator prey domain.
***************************************************************************/

#include "ReturnData.h"

class ReturnMove : public ReturnData
{
   private:
      int moveDirection;

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. 
      ************************************************/ 
      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      static const int UP;
      static const int DOWN;
      static const int LEFT;
      static const int RIGHT;

      ReturnMove();
      virtual ~ReturnMove();

      void setData(int data);
      int getData() const;
   protected:
};

#endif
