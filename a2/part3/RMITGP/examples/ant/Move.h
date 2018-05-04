#ifndef _MOVE_H_
#define _MOVE_H_

/******************************************************************************
 Header file
 Class:        Move 
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 The Move terminal is from the santa fe ant problem. The move terminal
 causes the ant to move forward one space.
***************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class Move : public Terminal 
{
   private:

   public:
      Move(GPConfig *conf);
      virtual ~Move();

      static Terminal* generate(const string &name, GPConfig *conf);

      virtual void evaluate(ReturnData *out);  
      virtual void print(string &s);

      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();

   protected:
};

#endif
