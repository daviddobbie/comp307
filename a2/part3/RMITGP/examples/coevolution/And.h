#ifndef _AND_H_
#define _AND_H_

/******************************************************************************
 Header file
 Class:        And
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 Boolean and function. 
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class And : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      And(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~And();

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
