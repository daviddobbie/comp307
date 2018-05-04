/******************************************************************************
 Definition file
 Class:        Prog2
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>
using namespace std;

#include "Prog2.h"
#include "ReturnDummy.h"

#include "GPConfig.h"

Prog2::Prog2(GPConfig *conf) : Function(ReturnDummy::TYPENUM, 2, "Prog2", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnDummy::TYPENUM);   
   }
}

Prog2::~Prog2() 
{
}

Function* Prog2::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "Prog2")
      return new Prog2(conf);

   return NULL;     
}

void Prog2::evaluate(ReturnData *out)
{
   //We don't check the ReturnData object (out) is of the correct type
   //because we don't use it, and don't care what type it is 

   getArgN(0)->evaluate(out); 
   getArgN(1)->evaluate(out);
}

Node* Prog2::copy()
{
   int i;
   Function *tmp = new Prog2(config);

   if (tmp == NULL)
      throw string("Prog2::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
