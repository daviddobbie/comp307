#ifndef _RETURNPOWER_H_
#define _RETURNPOWER_H_

/******************************************************************************
 Header file
 Class:        ReturnPower
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 ReturnPower represents a power in robocup. A power can be used
 for dashing and for kicking a ball. 
***************************************************************************/

#include "ReturnData.h"

class ReturnPower : public ReturnData
{
   private:
      double data; //The power

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. 
      ************************************************/ 
      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      ReturnPower();
      virtual ~ReturnPower();

      /************************
       Set the data to be num
      ************************/
      void setData(double num);
     
      /****************************
       Get the data of this class 
      ****************************/
      double getData() const;
     
   protected:
};

#endif
