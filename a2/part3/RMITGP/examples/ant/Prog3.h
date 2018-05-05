#ifndef _PROG3_H_
#define _PROG3_H_

/******************************************************************************
 Header file
 Class:        Prog3
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 Prog3 is a function which accepts three arguments, and executes all 3 of
 them in succession.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Prog3 : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Prog3(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Prog3();

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
