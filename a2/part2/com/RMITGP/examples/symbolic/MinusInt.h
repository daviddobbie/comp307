#ifndef _MINUSINT_H_
#define _MINUSINT_H_

/******************************************************************************
 Header file
 Class:        MinusInt
 Date created: 01/07/2002
 Written by:   Dylan Mawhinney

 MinusInt is a sub class of Function, it accepts two integers as
 arguments and returns the difference of it's two arguments.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class MinusInt : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      MinusInt(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~MinusInt();

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
