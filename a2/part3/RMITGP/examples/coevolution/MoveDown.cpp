/******************************************************************************
 Definition file
 Class:        MoveDown
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "MoveDown.h"
#include "ReturnMove.h"

#include "GPConfig.h"

MoveDown::MoveDown(GPConfig *conf) : Terminal(ReturnMove::TYPENUM, "moveDown", conf)
{
}

MoveDown::~MoveDown()
{
}

Terminal* MoveDown::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "moveDown")
      return new MoveDown(conf);

   return NULL;     
}


void MoveDown::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnMove::TYPENUM))
      throw string("MoveDown::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnMove *>(out)->setData(ReturnMove::DOWN);
}

Node* MoveDown::copy()
{
   Node *tmp = new MoveDown(config);

   if (tmp == NULL)
      throw string("MoveDown::copy() Error, out of memory");

   return tmp;
}

