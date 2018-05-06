#ifndef _MOVELEFT_H_
#define _MOVELEFT_H_

/******************************************************************************
 Header file
 Class:        MoveLeft
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 MoveLeft is a terminal which when executed causes the predator or prey
 to move left on the grid.
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class MoveLeft : public Terminal 
{
   private:

   public:
      MoveLeft(GPConfig *conf);
      virtual ~MoveLeft();

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
