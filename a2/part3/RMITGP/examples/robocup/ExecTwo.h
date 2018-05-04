#ifndef _EXECTWO_H_
#define _EXECTWO_H_

/******************************************************************************
 Header file
 Class:        ExecTwo 
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 ExecTwo is a function which executes two arguments.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class ExecTwo : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      ExecTwo(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~ExecTwo();

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
