#ifndef _RETURNANGLE_H_
#define _RETURNANGLE_H_

/******************************************************************************
 Header file
 Class:        ReturnAngle
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 ReturnAngle represents an angle in robocup. An angle can be used
 for turning and for kicking a ball. 
***************************************************************************/

#include "ReturnData.h"

class ReturnAngle : public ReturnData
{
   private:
      double data; //The angle 

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. 
      ************************************************/ 
      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      ReturnAngle();
      virtual ~ReturnAngle();

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
