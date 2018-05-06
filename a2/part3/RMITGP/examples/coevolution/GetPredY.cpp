/******************************************************************************
 Definition file
 Class:        GetPredY
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "GetPredY.h"
#include "ReturnCoord.h"

#include "PredatorPreyFitness.h"

#include "GPConfig.h"

GetPredY::GetPredY(GPConfig *conf) : Terminal(ReturnCoord::TYPENUM, "getPredY", conf)
{
}

GetPredY::~GetPredY()
{
}

Terminal* GetPredY::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "getPredY")
      return new GetPredY(conf);

   return NULL;     
}


void GetPredY::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnCoord::TYPENUM))
      throw string("GetPredY::evaluate, incorrect ReturnData type");

   int x = dynamic_cast<PredatorPreyFitness *>(config->fitnessObject)
                                              ->getPredY();

   dynamic_cast<ReturnCoord *>(out)->setData(x);
}

Node* GetPredY::copy()
{
   Node *tmp = new GetPredY(config);

   if (tmp == NULL)
      throw string("GetPredY::copy() Error, out of memory");

   return tmp;
}

