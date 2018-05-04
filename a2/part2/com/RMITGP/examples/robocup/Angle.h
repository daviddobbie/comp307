#ifndef _ANGLE_H_
#define _ANGLE_H_

/******************************************************************************
 Header file
 Class:        GPAngle
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 GPAngle is a terminal which represents an angle argument which could be
 supplied to a turn or kick function. 

 The name GPAngle is necessary because there is a type already in the
 robocup server code which is called Angle.
***************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class GPAngle : public Terminal 
{
   private:
      double value; //The angle for this terminal 

   public:
      GPAngle(GPConfig *conf);
      explicit GPAngle(double initValue, GPConfig *conf);
      virtual ~GPAngle();

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
