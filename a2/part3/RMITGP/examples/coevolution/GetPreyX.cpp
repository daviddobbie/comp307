/******************************************************************************
 Definition file
 Class:        GetPreyX
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "GetPreyX.h"
#include "ReturnCoord.h"

#include "PredatorPreyFitness.h"

#include "GPConfig.h"

GetPreyX::GetPreyX(GPConfig *conf) : Terminal(ReturnCoord::TYPENUM, "getPreyX", conf)
{
}

GetPreyX::~GetPreyX()
{
}

Terminal* GetPreyX::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "getPreyX")
      return new GetPreyX(conf);

   return NULL;     
}


void GetPreyX::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnCoord::TYPENUM))
      throw string("GetPreyX::evaluate, incorrect ReturnData type");

   int x = dynamic_cast<PredatorPreyFitness *>(config->fitnessObject)
                                              ->getPreyX();

   dynamic_cast<ReturnCoord *>(out)->setData(x);
}

Node* GetPreyX::copy()
{
   Node *tmp = new GetPreyX(config);

   if (tmp == NULL)
      throw string("GetPreyX::copy() Error, out of memory");

   return tmp;
}

