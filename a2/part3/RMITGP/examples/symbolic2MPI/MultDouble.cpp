/******************************************************************************
 Definition file
 Class:        MultDouble 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "MultDouble.h"
#include "ReturnDouble.h"
#include <float.h>
#include <cmath>

MultDouble::MultDouble(GPConfig *conf) :
                            Function(ReturnDouble::TYPENUM, 2, "d*", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnDouble::TYPENUM);   
   }
}

MultDouble::~MultDouble()
{
}

Function* MultDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new MultDouble(conf);
   else if (name == "d*")
      return new MultDouble(conf);

   return NULL;     
}

void MultDouble::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnDouble::TYPENUM)
      throw string("MultDouble::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("MultDouble::evaluate Error argument has incorrect return type");
      }
   }

   ReturnDouble r1, r2;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2);

   double result = r1.getData() * r2.getData();
#ifdef WIN32
                  if (!_finite(result))
#else
                  if (!isfinite(result))
#endif
	 result = DBL_MAX;
   
   
   dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* MultDouble::copy()
{
   int i;
   Function *tmp = new MultDouble(config);

   if (tmp == NULL)
      throw string("MultDouble::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
