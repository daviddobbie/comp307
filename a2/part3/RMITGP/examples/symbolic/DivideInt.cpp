/******************************************************************************
 Definition file
 Class:        DivideInt
 Date created: 01/07/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>
#include <iostream>

using namespace std;

#include "DivideInt.h"
#include "ReturnInt.h"

#include "GPConfig.h"

#include <cfloat>
#include <limits.h>

DivideInt::DivideInt(GPConfig *conf)
                             : Function(ReturnInt::TYPENUM, 2, "i/", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnInt::TYPENUM);   
   }
}

DivideInt::~DivideInt() 
{
}

Function* DivideInt::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new DivideInt(conf);
   else if (name == "i/")
      return new DivideInt(conf);

   return NULL;     
}

void DivideInt::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnInt::TYPENUM)
      throw string("DivideInt::evaluate, incorrect ReturnData type");
  
   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("DivideInt::evaluate Error argument has incorrect return type");
      }
   }

   ReturnInt r1, r2;
   int result;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2);

   if (r2.getData() != 0)
      result = r1.getData() / r2.getData();
   else
      result = INT_MAX;

   dynamic_cast<ReturnInt *>(out)->setData(result); 
}

Node* DivideInt::copy()
{
   int i;
   Function *tmp = new DivideInt(config);

   if (tmp == NULL)
      throw string("DivideInt::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
