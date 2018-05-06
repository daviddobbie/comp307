#ifndef _MOVEDOWN_H_
#define _MOVEDOWN_H_

/******************************************************************************
 Header file
 Class:        MoveDown
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 MoveDown is a terminal which when executed causes the predator or prey
 to move down on the grid.
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class MoveDown : public Terminal 
{
   private:

   public:
      MoveDown(GPConfig *conf);
      virtual ~MoveDown();

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
