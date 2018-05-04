#ifndef _RETURN_H_
#define _RETURN_H_

/******************************************************************************
 Header file
 Class:        ReturnDummy
 Date created: 02/08/2002
 Written by:   Dylan Mawhinney

 ReturnDummy is just a dummy return class, use this when you don't really
 need to return anything at all. 
***************************************************************************/

#include "ReturnData.h"

class ReturnDummy : public ReturnData
{
   private:
      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. 
      ************************************************/ 
      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      ReturnDummy();
      virtual ~ReturnDummy();
   protected:
};

#endif
