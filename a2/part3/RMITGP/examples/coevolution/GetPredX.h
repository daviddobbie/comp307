#ifndef _GETPREDX_H_
#define _GETPREDX_H_

/******************************************************************************
 Header file
 Class:        GetPredX
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 GetPredX is a terminal which returns the current x coordinate of the
 predator. 
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class GetPredX : public Terminal 
{
   private:

   public:
      GetPredX(GPConfig *conf);
      virtual ~GetPredX();

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
