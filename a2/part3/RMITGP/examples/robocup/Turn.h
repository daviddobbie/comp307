#ifndef _TURN_H_
#define _TURN_H_

/******************************************************************************
 Header file
 Class:        Turn 
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 Turn is function which causes the player to turn with a 
 specified angle. The function accepts one parameter (an angle).
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Turn : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Turn(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Turn();

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
