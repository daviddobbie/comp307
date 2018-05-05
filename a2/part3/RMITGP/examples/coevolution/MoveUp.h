#ifndef _MOVEUP_H_
#define _MOVEUP_H_

/******************************************************************************
 Header file
 Class:        MoveUp
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 MoveUp is a terminal which when executed causes the predator or prey
 to move up on the grid.
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class MoveUp : public Terminal 
{
   private:

   public:
      MoveUp(GPConfig *conf);
      virtual ~MoveUp();

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
