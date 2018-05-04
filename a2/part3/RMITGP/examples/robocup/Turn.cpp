/******************************************************************************
 Definition file
 Class:        Turn 
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "Turn.h"
#include "ReturnAction.h"
#include "ReturnAngle.h"

#include "GPConfig.h"

Turn::Turn(GPConfig *conf) : Function(ReturnAction::TYPENUM, 1, "turn", conf)
{
   setArgNReturnType(0, ReturnAngle::TYPENUM);   
}

Turn::~Turn()
{
}

Function* Turn::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new Turn(conf);
   else if (name == "turn")
      return new Turn(conf);

   return NULL;     
}

void Turn::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnAction::TYPENUM)
      throw string("Turn::evaluate, incorrect ReturnData type");

   if (getArgNReturnType(0) != getArgN(0)->getReturnType())
   {
      throw string("Turn::evaluate Error argument has incorrect return type");
   }

   ReturnAngle r1;

   getArgN(0)->evaluate(&r1); 

   //Add a turn action to the ReturnAction list.
   //Use the angle obtained through the first argument to this 
   //function as the angle.
   dynamic_cast<ReturnAction *>(out)->addTurn(r1.getData()); 
}

Node* Turn::copy()
{
   int i;
   Function *tmp = new Turn(config);

   if (tmp == NULL)
      throw string("Turn::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
