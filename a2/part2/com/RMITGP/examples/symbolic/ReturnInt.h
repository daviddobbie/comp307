#ifndef _RETURNINT_H_
#define _RETURNINT_H_

/******************************************************************************
 Header file
 Class:        ReturnInt
 Date created: 19/03/2002
 Written by:   Dylan Mawhinney

 ReturnInt is a derived class of ReturnData, it represents an integer
 returned from a GP node (see Node class).
 
***************************************************************************/

#include "ReturnData.h"

class ReturnInt : public ReturnData
{
   private:
      int data; //The data for this class 

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. 
      ************************************************/ 
      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      ReturnInt();
      virtual ~ReturnInt();

      /************************
       Set the data to be num
      ************************/
      void setData(int num);
     
      /****************************
       Get the data of this class 
      ****************************/
      int getData() const;
     
   protected:

};

#endif
