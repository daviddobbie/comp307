#ifndef _GREATERTHAN_H_
#define _GREATERTHAN_H_

/******************************************************************************
 Header file
 Class:        GreaterThan 
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 GreaterThan is a function which accepts two coordinates and returns true
 if the first argument is greater than the second argument.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class GreaterThan : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      GreaterThan(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~GreaterThan();

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
