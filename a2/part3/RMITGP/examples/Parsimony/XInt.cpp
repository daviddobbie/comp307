/******************************************************************************
 Definition file
 Class:        XInt
 Date created: 08/06/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <cstdio> //for sprintf
#include <string>

using namespace std;

#include "XInt.h"
#include "ReturnInt.h"

#include "GPConfig.h"

int XInt::value = 0;

XInt::XInt(GPConfig *conf) : Terminal(ReturnInt::TYPENUM, "X", conf) 
{
}

XInt::~XInt()
{
}

Terminal* XInt::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new XInt(conf);
   if (name == "X")
      return new XInt(conf);

   return NULL;
}


void XInt::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnInt::TYPENUM))
      throw string("RandInt::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnInt *>(out)->setData(value);
}

Node* XInt::copy()
{
   Node *tmp = new XInt(config);

   if (tmp == NULL)
      throw string("XInt::copy() Error, out of memory");

   return tmp;
}

void XInt::setValue(int v)
{
   value = v;
}
