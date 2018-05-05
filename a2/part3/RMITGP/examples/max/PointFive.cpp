/******************************************************************************
 Definition file
 Class:        PointFive
 Date created: 19/11/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdio> //for sprintf
#include <string>

using namespace std;

#include "GPConfig.h"

#include "PointFive.h"
#include "ReturnDouble.h"

PointFive::PointFive(GPConfig *conf) :
                           Terminal(ReturnDouble::TYPENUM, "0.5", conf)
{
}

PointFive::~PointFive()
{
}

Terminal* PointFive::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "0.5")
      return new PointFive(conf);

   return NULL;      
}

void PointFive::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("PointFive::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(0.5);
}

Node* PointFive::copy()
{
   Node *tmp = new PointFive(config);

   if (tmp == NULL)
      throw string("PointFive::copy() Error, out of memory");

   return tmp;
}
