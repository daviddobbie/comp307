#ifndef _POINTFIVE_H_
#define _POINTFIVE_H_

/******************************************************************************
 Header file
 Class:        PointFive
 Date created: 19/11/2002
 Written by:   Dylan Mawhinney

 PointFive is a terminal which always has the value 0.5. 
***************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class PointFive : public Terminal 
{
   private:

   public:
      PointFive(GPConfig *conf);
      virtual ~PointFive();

      static Terminal* generate(const string &name, GPConfig *conf);

      virtual void evaluate(ReturnData *out);  

      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();
   protected:

};

#endif
