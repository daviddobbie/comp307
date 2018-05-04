/******************************************************************************
 Definition file
 Class:        LessThan 
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "LessThan.h"
#include "ReturnCoord.h"
#include "ReturnBoolean.h"

#include "GPConfig.h"

LessThan::LessThan(GPConfig *conf)
                       : Function(ReturnBoolean::TYPENUM, 2, "<", conf)
{
   setArgNReturnType(0, ReturnCoord::TYPENUM); 
   setArgNReturnType(1, ReturnCoord::TYPENUM);
}

LessThan::~LessThan()
{
}

Function* LessThan::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new LessThan(conf);
   else if (name == "<")
      return new LessThan(conf);

   return NULL;     
}

void LessThan::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnBoolean::TYPENUM)
      throw string("LessThan::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("LessThan::evaluate Error argument has incorrect return type");
      }
   }

   ReturnCoord r1;
   ReturnCoord r2;
   bool result;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2); 

   result = r1.getData() < r2.getData();

   dynamic_cast<ReturnBoolean *>(out)->setData(result); 
}

Node* LessThan::copy()
{
   int i;
   Function *tmp = new LessThan(config);

   if (tmp == NULL)
      throw string("LessThan::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
