#ifndef _MOVERIGHT_H_
#define _MOVERIGHT_H_

/******************************************************************************
 Header file
 Class:        MoveRight
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 MoveRight is a terminal which when executed causes the predator or prey
 to move right on the grid.
***************************************************************************/

class GPConfig;

#include <string>

#include "Terminal.h"

class MoveRight : public Terminal 
{
   private:

   public:
      MoveRight(GPConfig *conf);
      virtual ~MoveRight();

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
