#ifndef _IFFOODAHEAD_H_
#define _IFFOODAHEAD_H_

/******************************************************************************
 Header file
 Class:        IfFoodAhead 
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 IfFoodAhead accepts two arguments the first argument is executed if
 there is food in front of the ant, then second argument is executed
 if there is no food in front of the ant.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class IfFoodAhead : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      IfFoodAhead(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~IfFoodAhead();

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
