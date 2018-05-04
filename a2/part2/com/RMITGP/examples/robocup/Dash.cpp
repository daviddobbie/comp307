/******************************************************************************
 Definition file
 Class:        Dash 
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "Dash.h"
#include "ReturnAction.h"
#include "ReturnPower.h"

#include "GPConfig.h"

Dash::Dash(GPConfig *conf) : Function(ReturnAction::TYPENUM, 1, "dash", conf)
{
   setArgNReturnType(0, ReturnPower::TYPENUM);   
}

Dash::~Dash()
{
}

Function* Dash::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new Dash(conf);
   else if (name == "dash")
      return new Dash(conf);

   return NULL;     
}

void Dash::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnAction::TYPENUM)
      throw string("Dash::evaluate, incorrect ReturnData type");

   if (getArgNReturnType(0) != getArgN(0)->getReturnType())
   {
      throw string("Dash::evaluate Error argument has incorrect return type");
   }

   ReturnPower r1;

   getArgN(0)->evaluate(&r1); 

   //Add a dash action to the ReturnAction list.
   //Use the power obtained through the first argument to this 
   //function as the power.
   dynamic_cast<ReturnAction *>(out)->addDash(r1.getData()); 
}

Node* Dash::copy()
{
   int i;
   Function *tmp = new Dash(config);

   if (tmp == NULL)
      throw string("Dash::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
