/******************************************************************************
 Definition file
 Class:        MultInt
 Date created: 01/07/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>
#include <iostream>

using namespace std;

#include "MultInt.h"
#include "ReturnInt.h"

#include "GPConfig.h"

MultInt::MultInt(GPConfig *conf)
                              : Function(ReturnInt::TYPENUM, 2, "i*", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnInt::TYPENUM);   
   }
}

MultInt::~MultInt() 
{
}

Function* MultInt::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new MultInt(conf);
   else if (name == "i*")
      return new MultInt(conf);

   return NULL;     
}

void MultInt::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnInt::TYPENUM)
      throw string("MultInt::evaluate, incorrect ReturnData type");
  
   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("MultInt::evaluate Error argument has incorrect return type");
      }
   }

   ReturnInt r1, r2;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2);

   int result = r1.getData() * r2.getData();

   dynamic_cast<ReturnInt *>(out)->setData(result); 
}

Node* MultInt::copy()
{
   int i;
   Function *tmp = new MultInt(config);

   if (tmp == NULL)
      throw string("MultInt::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
