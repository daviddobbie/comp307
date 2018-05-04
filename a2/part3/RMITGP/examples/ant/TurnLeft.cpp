/******************************************************************************
 Definition file
 Class:        TurnLeft
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <string>
using namespace std;

#include "SantaFeFitness.h"
#include "TurnLeft.h"
#include "ReturnDummy.h"

#include "GPConfig.h"

TurnLeft::TurnLeft(GPConfig *conf) 
                          : Terminal(ReturnDummy::TYPENUM, "turnLeft", conf)
{
}

TurnLeft::~TurnLeft()
{
}

Terminal* TurnLeft::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "turnLeft")
      return new TurnLeft(conf);

   return NULL;     
}


void TurnLeft::evaluate(ReturnData *out)  
{
   //We don't check the ReturnData object (out) is of the correct type
   //because we don't use it, and don't care what type it is 

   dynamic_cast<SantaFeFitness *>(config->fitnessObject)->turnLeft();
}

void TurnLeft::print(string &s)
{
   s.append("turnLeft"); 
}

Node* TurnLeft::copy()
{
   Node *tmp = generate("", config); 

   if (tmp == NULL)
      throw string("TurnLeft::copy() Error, out of memory");

   return tmp;
}
