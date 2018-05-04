/******************************************************************************
 Definition file
 Class:        Prog3
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>
using namespace std;

#include "Prog3.h"
#include "ReturnDummy.h"

#include "GPConfig.h"

Prog3::Prog3(GPConfig *conf) : Function(ReturnDummy::TYPENUM, 3, "Prog3", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnDummy::TYPENUM);   
   }
}

Prog3::~Prog3() 
{
}

Function* Prog3::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "Prog3")
      return new Prog3(conf);

   return NULL;     
}

void Prog3::evaluate(ReturnData *out)
{
   //We don't check the ReturnData object (out) is of the correct type
   //because we don't use it, and don't care what type it is 

   getArgN(0)->evaluate(out); 
   getArgN(1)->evaluate(out);
   getArgN(2)->evaluate(out);
}

Node* Prog3::copy()
{
   int i;
   Function *tmp = new Prog3(config);

   if (tmp == NULL)
      throw string("Prog3::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
