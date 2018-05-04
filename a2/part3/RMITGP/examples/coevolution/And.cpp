/******************************************************************************
 Definition file
 Class:        And 
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "And.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

And::And(GPConfig *conf) : Function(ReturnBoolean::TYPENUM, 2, "and", conf)
{
   setArgNReturnType(0, ReturnBoolean::TYPENUM); //first argument bool
   setArgNReturnType(1, ReturnBoolean::TYPENUM); //second bool 
}

And::~And()
{
}

Function* And::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new And(conf);
   else if (name == "and")
      return new And(conf);

   return NULL;     
}

void And::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnBoolean::TYPENUM)
      throw string("And::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("And::evaluate Error argument has incorrect return type");
      }
   }

   ReturnBoolean rb1, rb2;

   getArgN(0)->evaluate(&rb1); 
   getArgN(1)->evaluate(&rb2);

   dynamic_cast<ReturnBoolean *>(out)->setData(rb1.getData() && rb2.getData()); 
}

Node* And::copy()
{
   int i;
   Function *tmp = new And(config);

   if (tmp == NULL)
      throw string("And::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
