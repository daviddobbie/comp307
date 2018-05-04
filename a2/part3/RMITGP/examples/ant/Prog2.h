#ifndef _PROG2_H_
#define _PROG2_H_

/******************************************************************************
 Header file
 Class:        Prog2
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 Prog2 is a function which accepts two arguments, and executes both of them.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Prog2 : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Prog2(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Prog2();

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
