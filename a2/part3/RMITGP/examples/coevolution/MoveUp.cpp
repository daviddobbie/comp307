/******************************************************************************
 Definition file
 Class:        MoveUp
 Date created: 20/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <string>

using namespace std;

#include "MoveUp.h"
#include "ReturnMove.h"

#include "GPConfig.h"

MoveUp::MoveUp(GPConfig *conf) : Terminal(ReturnMove::TYPENUM, "moveUp", conf)
{
}

MoveUp::~MoveUp()
{
}

Terminal* MoveUp::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "moveUp")
      return new MoveUp(conf);

   return NULL;     
}


void MoveUp::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnMove::TYPENUM))
      throw string("MoveUp::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnMove *>(out)->setData(ReturnMove::UP);
}

Node* MoveUp::copy()
{
   Node *tmp = new MoveUp(config);

   if (tmp == NULL)
      throw string("MoveUp::copy() Error, out of memory");

   return tmp;
}

