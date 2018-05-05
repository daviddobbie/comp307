/******************************************************************************
 Definition file
 Class:        Or 
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "Or.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

Or::Or(GPConfig *conf) : Function(ReturnBoolean::TYPENUM, 2, "or", conf)
{
   setArgNReturnType(0, ReturnBoolean::TYPENUM); //first argument bool
   setArgNReturnType(1, ReturnBoolean::TYPENUM); //second bool 
}

Or::~Or()
{
}

Function* Or::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new Or(conf);
   else if (name == "or")
      return new Or(conf);

   return NULL;     
}

void Or::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnBoolean::TYPENUM)
      throw string("Or::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("Or::evaluate Error argument has incorrect return type");
      }
   }

   ReturnBoolean rb1, rb2;

   getArgN(0)->evaluate(&rb1); 
   getArgN(1)->evaluate(&rb2);

   dynamic_cast<ReturnBoolean *>(out)->setData(rb1.getData() || rb2.getData()); 
}

Node* Or::copy()
{
   int i;
   Function *tmp = new Or(config);

   if (tmp == NULL)
      throw string("Or::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
