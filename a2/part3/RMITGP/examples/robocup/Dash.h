#ifndef _DASH_H_
#define _DASH_H_

/******************************************************************************
 Header file
 Class:        Dash 
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 Dash is function which causes the player to move forward with a 
 specified power. The function accepts one parameter (a power).
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Dash : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Dash(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Dash();

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
