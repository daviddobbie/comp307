/******************************************************************************
 Definition file
 Class:        Move
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <string>

using namespace std;

#include "SantaFeFitness.h"
#include "Move.h"
#include "ReturnDummy.h"

#include "GPConfig.h"

Move::Move(GPConfig *conf) : Terminal(ReturnDummy::TYPENUM, "move", conf)
{
}

Move::~Move()
{
}

Terminal* Move::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "move")
      return new Move(conf);

   return NULL;     
}


void Move::evaluate(ReturnData *out)  
{
   //We don't check the ReturnData object (out) is of the correct type
   //because we don't use it, and don't care what type it is 

   dynamic_cast<SantaFeFitness *>(config->fitnessObject)->move();
}

void Move::print(string &s)
{
   s.append("move"); 
}

Node* Move::copy()
{
   Node *tmp = generate("", config); 

   if (tmp == NULL)
      throw string("Move::copy() Error, out of memory");

   return tmp;
}
