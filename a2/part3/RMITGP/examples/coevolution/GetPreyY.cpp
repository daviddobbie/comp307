/******************************************************************************
 Definition file
 Class:        GetPreyY
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "GetPreyY.h"
#include "ReturnCoord.h"

#include "PredatorPreyFitness.h"

#include "GPConfig.h"

GetPreyY::GetPreyY(GPConfig *conf) : Terminal(ReturnCoord::TYPENUM, "getPreyY", conf)
{
}

GetPreyY::~GetPreyY()
{
}

Terminal* GetPreyY::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "getPreyY")
      return new GetPreyY(conf);

   return NULL;     
}


void GetPreyY::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnCoord::TYPENUM))
      throw string("GetPreyY::evaluate, incorrect ReturnData type");

   int x = dynamic_cast<PredatorPreyFitness *>(config->fitnessObject)
                                              ->getPreyY();

   dynamic_cast<ReturnCoord *>(out)->setData(x);
}

Node* GetPreyY::copy()
{
   Node *tmp = new GetPreyY(config);

   if (tmp == NULL)
      throw string("GetPreyY::copy() Error, out of memory");

   return tmp;
}

