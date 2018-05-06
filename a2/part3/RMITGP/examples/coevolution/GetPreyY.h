#ifndef _GETPREYY_H_
#define _GETPREYY_H_

/******************************************************************************
 Header file
 Class:        GetPreyY
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 GetPreyY is a terminal which returns the current y coordinate of the
 prey. 
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class GetPreyY : public Terminal 
{
   private:

   public:
      GetPreyY(GPConfig *conf);
      virtual ~GetPreyY();

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
