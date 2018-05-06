#ifndef _OR_H_
#define _OR_H_

/******************************************************************************
 Header file
 Class:        Or 
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 Boolean or function. 
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Or : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Or(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Or();

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
