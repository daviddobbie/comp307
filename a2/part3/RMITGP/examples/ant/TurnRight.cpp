/******************************************************************************
 Definition file
 Class:        TurnRight
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <string>
using namespace std;

#include "SantaFeFitness.h"
#include "TurnRight.h"
#include "ReturnDummy.h"

#include "GPConfig.h"

TurnRight::TurnRight(GPConfig *conf) 
                           : Terminal(ReturnDummy::TYPENUM, "turnRight", conf)
{
}

TurnRight::~TurnRight()
{
}

Terminal* TurnRight::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "turnRight")
      return new TurnRight(conf);

   return NULL;     
}


void TurnRight::evaluate(ReturnData *out)  
{
   //We don't check the ReturnData object (out) is of the correct type
   //because we don't use it, and don't care what type it is 

   dynamic_cast<SantaFeFitness *>(config->fitnessObject)->turnRight();
}

void TurnRight::print(string &s)
{
   s.append("turnRight"); 
}

Node* TurnRight::copy()
{
   Node *tmp = generate("", config); 

   if (tmp == NULL)
      throw string("TurnRight::copy() Error, out of memory");

   return tmp;
}
