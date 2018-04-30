#ifndef _LESSTHAN_H_
#define _LESSTHAN_H_

/******************************************************************************
 Header file
 Class:        LessThan 
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 LessThan is a function which accepts two coordinates and returns true
 if the first argument is less than the second argument.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class LessThan : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      LessThan(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~LessThan();

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
