#ifndef _GETPREDY_H_
#define _GETPREDY_H_

/******************************************************************************
 Header file
 Class:        GetPredY
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 GetPredY is a terminal which returns the current y coordinate of the
 predator. 
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class GetPredY : public Terminal 
{
   private:

   public:
      GetPredY(GPConfig *conf);
      virtual ~GetPredY();

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
