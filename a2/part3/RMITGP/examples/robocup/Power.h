#ifndef _POWER_H_
#define _POWER_H_

/******************************************************************************
 Header file
 Class:        Power
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 Power is a terminal which represents a power argument which could be
 supplied to a dash or kick function. 
***************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class Power : public Terminal 
{
   private:
      double value; //The power for this terminal 

   public:
      Power(GPConfig *conf);
      explicit Power(double initValue, GPConfig *conf);
      virtual ~Power();

      static Terminal* generate(const string &name, GPConfig *conf);

      virtual void evaluate(ReturnData *out);  
      virtual void print(string &s);

      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();
   protected:

};

#endif
