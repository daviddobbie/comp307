#ifndef _RETURNCOORD_H_
#define _RETURNCOORD_H_

/******************************************************************************
 Header file
 Class:        ReturnCoord
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 ReturnCoord is a ReturnData object which is used to return the coordinates
 of the predator and prey on the grid.
***************************************************************************/

#include "ReturnData.h"

class ReturnCoord : public ReturnData
{
   private:
      int data; //The data for this class 

      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      ReturnCoord();
      virtual ~ReturnCoord();

      void setData(int num);
     
      int getData() const;
     
   protected:

};

#endif
