/******************************************************************************
 Definition file
 Class:        IfFoodAhead
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "SantaFeFitness.h"

#include "IfFoodAhead.h"

#include "ReturnDummy.h"

#include "GPConfig.h"

IfFoodAhead::IfFoodAhead(GPConfig *conf) 
                      : Function(ReturnDummy::TYPENUM, 2, "IfFoodAhead", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnDummy::TYPENUM);   
   }
}

IfFoodAhead::~IfFoodAhead() 
{
}

Function* IfFoodAhead::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "IfFoodAhead")
      return new IfFoodAhead(conf);

   return NULL;     
}

void IfFoodAhead::evaluate(ReturnData *out)
{
   //We don't check the ReturnData object (out) is of the correct type
   //because we don't use it, and don't care what type it is 
   bool ahead = 
         dynamic_cast<SantaFeFitness *>(config->fitnessObject)->ifFoodAhead();

   if (ahead)
      getArgN(0)->evaluate(out); 
   else
      getArgN(1)->evaluate(out);
}

Node* IfFoodAhead::copy()
{
   int i;
   Function *tmp = new IfFoodAhead(config);

   if (tmp == NULL)
      throw string("IfFoodAhead::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
