#ifndef _DIVIDEINT_H_
#define _DIVIDEINT_H_

/******************************************************************************
 Header file
 Class:        DivideInt
 Date created: 01/07/2002
 Written by:   Dylan Mawhinney

 DivideInt is a sub class of Function, it accepts two integers as
 arguments and returns the quotient of it's two arguments.
******************************************************************************/
class GPConfig;

#include <string>
#include "Function.h"

class DivideInt : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      DivideInt(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~DivideInt();

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
