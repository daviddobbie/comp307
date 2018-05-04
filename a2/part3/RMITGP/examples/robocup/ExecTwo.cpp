/******************************************************************************
 Definition file
 Class:        ExecTwo 
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "ExecTwo.h"
#include "ReturnAction.h"

#include "GPConfig.h"

ExecTwo::ExecTwo(GPConfig *conf)
                  : Function(ReturnAction::TYPENUM, 2, "execTwo", conf)
{
   setArgNReturnType(0, ReturnAction::TYPENUM);   
   setArgNReturnType(1, ReturnAction::TYPENUM);   
}

ExecTwo::~ExecTwo()
{
}

Function* ExecTwo::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new ExecTwo(conf);
   else if (name == "execTwo")
      return new ExecTwo(conf);

   return NULL;     
}

void ExecTwo::evaluate(ReturnData *out)
{
   int i;
   if (out->getTypeNum() != ReturnAction::TYPENUM)
      throw string("ExecTwo::evaluate, incorrect ReturnData type");

   for (i=0; i < maxArgs; i++) 
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("ExecTwo::evaluate Error argument has incorrect return type");
      }
   }

   getArgN(0)->evaluate(out); 
   getArgN(1)->evaluate(out); 

   //This function doesn't return anything, it just evaluates it's arguments
   //so there is no need to add any data to the ReturnData object (out).
}

Node* ExecTwo::copy()
{
   int i;
   Function *tmp = new ExecTwo(config);

   if (tmp == NULL)
      throw string("ExecTwo::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
