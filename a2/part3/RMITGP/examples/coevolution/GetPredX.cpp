/******************************************************************************
 Definition file
 Class:        GetPredX
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "GetPredX.h"
#include "ReturnCoord.h"

#include "PredatorPreyFitness.h"

#include "GPConfig.h"

GetPredX::GetPredX(GPConfig *conf) : Terminal(ReturnCoord::TYPENUM, "getPredX", conf)
{
}

GetPredX::~GetPredX()
{
}

Terminal* GetPredX::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "getPredX")
      return new GetPredX(conf);

   return NULL;     
}


void GetPredX::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnCoord::TYPENUM))
      throw string("GetPredX::evaluate, incorrect ReturnData type");

   int x = dynamic_cast<PredatorPreyFitness *>(config->fitnessObject)
                                              ->getPredX();

   dynamic_cast<ReturnCoord *>(out)->setData(x);
}

Node* GetPredX::copy()
{
   Node *tmp = new GetPredX(config);

   if (tmp == NULL)
      throw string("GetPredX::copy() Error, out of memory");

   return tmp;
}

