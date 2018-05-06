#ifndef _XINT_H_
#define _XINT_H_

/******************************************************************************
 Header file
 Class:        XInt 
 Date created: 08/06/2002
 Written by:   Dylan Mawhinney

 XInt is a variable terminal. 
***************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class XInt : public Terminal 
{
   private:
      static int value; //The data for this class 

   public:
      XInt(GPConfig *conf);
      virtual ~XInt();

      static Terminal* generate(const string &name, GPConfig *conf);

      virtual void evaluate(ReturnData *out);  

      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();

      static void setValue(int v);

   protected:
};

#endif
