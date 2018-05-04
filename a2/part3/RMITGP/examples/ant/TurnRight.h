#ifndef _TURNRIGHT_H_
#define _TURNRIGHT_H_

/******************************************************************************
 Header file
 Class:        TurnRight 
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 The TurnRight terminal is from the santa fe ant problem. The turnleft terminal
 causes the ant to turn left.
***************************************************************************/

#include <string>

#include "Terminal.h"
#include "GPConfig.h"

class TurnRight : public Terminal 
{
   private:

   public:
      TurnRight(GPConfig *conf);
      virtual ~TurnRight();

      static Terminal* generate(const string &name, GPConfig *conf);

      virtual void evaluate(ReturnData *out);  
      virtual void print(string &s);

      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();

   protected:
};

#endif
