/******************************************************************************
 Definition file
 Class:        Kick 
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "Kick.h"
#include "ReturnAction.h"
#include "ReturnPower.h"
#include "ReturnAngle.h"

#include "GPConfig.h"

Kick::Kick(GPConfig *conf) : Function(ReturnAction::TYPENUM, 2, "kick", conf)
{
   setArgNReturnType(0, ReturnPower::TYPENUM);   
   setArgNReturnType(1, ReturnAngle::TYPENUM);   
}

Kick::~Kick()
{
}

Function* Kick::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new Kick(conf);
   else if (name == "kick")
      return new Kick(conf);

   return NULL;     
}

void Kick::evaluate(ReturnData *out)
{
   int i;
   if (out->getTypeNum() != ReturnAction::TYPENUM)
      throw string("Kick::evaluate, incorrect ReturnData type");

   for (i=0; i < maxArgs; i++) 
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("Kick::evaluate Error argument has incorrect return type");
      }
   }

   ReturnPower rp;
   ReturnAngle ra;
   

   getArgN(0)->evaluate(&rp); 
   getArgN(1)->evaluate(&ra); 

   //Add a kick action to the ReturnAction list.
   //Use the power and angle obtained through the arguments to this 
   //function as the power and angle.
   dynamic_cast<ReturnAction *>(out)->addKick(rp.getData(), ra.getData()); 
}

Node* Kick::copy()
{
   int i;
   Function *tmp = new Kick(config);

   if (tmp == NULL)
      throw string("Kick::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
