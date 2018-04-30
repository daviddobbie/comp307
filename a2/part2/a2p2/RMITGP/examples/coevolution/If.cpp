/******************************************************************************
 Definition file
 Class:        If 
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "If.h"
#include "ReturnMove.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

If::If(GPConfig *conf) : Function(ReturnMove::TYPENUM, 3, "if", conf)
{
   setArgNReturnType(0, ReturnBoolean::TYPENUM); //first argument bool
   setArgNReturnType(1, ReturnMove::TYPENUM);  //second and third 
   setArgNReturnType(2, ReturnMove::TYPENUM);  //doubles 
}

If::~If()
{
}

Function* If::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new If(conf);
   else if (name == "if")
      return new If(conf);

   return NULL;     
}

void If::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnMove::TYPENUM)
      throw string("If::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("If::evaluate Error argument has incorrect return type");
      }
   }

   ReturnBoolean rb;
   ReturnMove rm;

   getArgN(0)->evaluate(&rb); 

   //if the first argument was true execute 2nd argument
   if (rb.getData() == true)
      getArgN(1)->evaluate(&rm);
   //otherwise execute third argument
   else
      getArgN(2)->evaluate(&rm);

   dynamic_cast<ReturnMove *>(out)->setData(rm.getData()); 
}

Node* If::copy()
{
   int i;
   Function *tmp = new If(config);

   if (tmp == NULL)
      throw string("If::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
