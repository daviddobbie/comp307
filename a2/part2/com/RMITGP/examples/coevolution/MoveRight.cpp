/******************************************************************************
 Definition file
 Class:        MoveRight
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "MoveRight.h"
#include "ReturnMove.h"

#include "GPConfig.h"

MoveRight::MoveRight(GPConfig *conf) : Terminal(ReturnMove::TYPENUM, "moveRight", conf)
{
}

MoveRight::~MoveRight()
{
}

Terminal* MoveRight::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "moveRight")
      return new MoveRight(conf);

   return NULL;     
}


void MoveRight::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnMove::TYPENUM))
      throw string("MoveRight::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnMove *>(out)->setData(ReturnMove::RIGHT);
}

Node* MoveRight::copy()
{
   Node *tmp = new MoveRight(config);

   if (tmp == NULL)
      throw string("MoveRight::copy() Error, out of memory");

   return tmp;
}

