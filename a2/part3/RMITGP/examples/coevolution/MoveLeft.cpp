/******************************************************************************
 Definition file
 Class:        MoveLeft
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "MoveLeft.h"
#include "ReturnMove.h"

#include "GPConfig.h"

MoveLeft::MoveLeft(GPConfig *conf) : Terminal(ReturnMove::TYPENUM, "moveLeft", conf)
{
}

MoveLeft::~MoveLeft()
{
}

Terminal* MoveLeft::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "moveLeft")
      return new MoveLeft(conf);

   return NULL;     
}


void MoveLeft::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnMove::TYPENUM))
      throw string("MoveLeft::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnMove *>(out)->setData(ReturnMove::LEFT);
}

Node* MoveLeft::copy()
{
   Node *tmp = new MoveLeft(config);

   if (tmp == NULL)
      throw string("MoveLeft::copy() Error, out of memory");

   return tmp;
}

