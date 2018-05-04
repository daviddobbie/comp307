#ifndef _XDOUBLE_H_
#define _XDOUBLE_H_

/******************************************************************************
 Header file
 Class:        XDouble 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 XDouble is a variable terminal. 
***************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class XDouble : public Terminal 
{
   private:
      static double value; //The data for this class 

   public:
      XDouble(GPConfig *conf);
      virtual ~XDouble();

      static Terminal* generate(const string &name, GPConfig *conf);

      virtual void evaluate(ReturnData *out);  

      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();

      static void setValue(double v);

   protected:
};

#endif
