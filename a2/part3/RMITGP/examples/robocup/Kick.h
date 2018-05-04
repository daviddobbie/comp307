#ifndef _KICK_H_
#define _KICK_H_

/******************************************************************************
 Header file
 Class:        Kick 
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 Kick is a function which causes the player to kick with a 
 specified power in a specified direction (angle). The function accepts
 two parameters (a power and an angle).
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Kick : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Kick(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Kick();

      static Function* generate(const string &name, GPConfig *conf);

      /********************
       Evaluate function
      ********************/
      virtual void evaluate(ReturnData *out);

      /***********************************
       Copies this function and it's 
       arguments and returns a pointer to
       the new copy.
      ***********************************/
      virtual Node* copy();

   protected:

};

#endif
