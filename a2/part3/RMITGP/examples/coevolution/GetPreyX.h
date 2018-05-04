#ifndef _GETPREYX_H_
#define _GETPREYX_H_

/******************************************************************************
 Header file
 Class:        GetPreyX
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 GetPreyX is a terminal which returns the current x coordinate of the
 prey. 
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class GetPreyX : public Terminal 
{
   private:

   public:
      GetPreyX(GPConfig *conf);
      virtual ~GetPreyX();

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
