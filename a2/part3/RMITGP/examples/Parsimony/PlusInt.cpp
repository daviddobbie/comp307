/******************************************************************************
 Definition file
 Class:        PlusInt
 Date created: 22/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>
#include <iostream>

using namespace std;

#include "PlusInt.h"
#include "ReturnInt.h"

#include "GPConfig.h"

PlusInt::PlusInt(GPConfig *conf) 
                                : Function(ReturnInt::TYPENUM, 2, "i+", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnInt::TYPENUM);   
   }
}

PlusInt::~PlusInt() 
{
}

Function* PlusInt::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new PlusInt(conf);
   else if (name == "i+")
      return new PlusInt(conf);

   return NULL;     
}

void PlusInt::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnInt::TYPENUM)
      throw string("PlusInt::evaluate, incorrect ReturnData type");

  
   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("PlusInt::evaluate Error argument has incorrect return type");
      }
   }

   ReturnInt r1, r2;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2);

   int result = r1.getData() + r2.getData();

   dynamic_cast<ReturnInt *>(out)->setData(result); 
}

Node* PlusInt::copy()
{
   int i;
   Function *tmp = new PlusInt(config);

   if (tmp == NULL)
      throw string("PlusInt::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
