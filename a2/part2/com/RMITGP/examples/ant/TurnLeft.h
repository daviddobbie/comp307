#ifndef _TURNLEFT_H_
#define _TURNLEFT_H_

/******************************************************************************
 Header file
 Class:        TurnLeft 
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 The TurnLeft terminal is from the santa fe ant problem. The turnleft terminal
 causes the ant to turn left.
***************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class TurnLeft : public Terminal 
{
   private:

   public:
      TurnLeft(GPConfig *conf);
      virtual ~TurnLeft();

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
