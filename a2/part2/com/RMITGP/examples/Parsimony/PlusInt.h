#ifndef _PLUSINT_H_
#define _PLUSINT_H_

/******************************************************************************
 Header file
 Class:        PlusInt
 Date created: 22/03/2002
 Written by:   Dylan Mawhinney

 PlusInt is a sub class of Function, it accepts two integers as
 arguments and returns the addition of it's two arguments.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class PlusInt : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      PlusInt(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~PlusInt();

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
