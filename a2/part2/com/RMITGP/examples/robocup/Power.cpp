/******************************************************************************
 Definition file
 Class:        Power
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdio> //for sprintf
#include <string>

using namespace std;

#include "Power.h"
#include "ReturnPower.h"

#include "GPConfig.h"

Power::Power(GPConfig *conf) : Terminal(ReturnPower::TYPENUM, "pow", conf),
                      value(config->randomNumGenerator->randReal() * 100.0)
{
}

Power::Power(double initValue, GPConfig *conf) :
                                  Terminal(ReturnPower::TYPENUM, "pow", conf),
                                  value(initValue)
{
}

Power::~Power()
{
}

Terminal* Power::generate(const string &name, GPConfig *conf)
{
   double tmpValue;
   string tmpName("pow");
   char copy[20];

   strcpy(copy, name.c_str());

   if (name == "")
      return new Power(conf);
#ifdef OLD_GCC 
   //Older versions of gcc 2.9X shipped with a c++ library which
   //had mistakes in implementation of some methods string::compare 
   //has it's parameters in the wrong order.

   else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
   else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
   {
      sscanf(copy, "pow%lf", &tmpValue);
      return new Power(tmpValue, conf);
   }

   return NULL;      
}

void Power::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnPower::TYPENUM))
      throw string("Power::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnPower *>(out)->setData(value);
}

void Power::print(string &s)
{
   char str[100]; 

   sprintf(str, "%s%f", getName().c_str(), value);
   s.append(str); 
}

Node* Power::copy()
{
   Node *tmp = new Power(value, config);

   if (tmp == NULL)
      throw string("Power::copy() Error, out of memory");

   return tmp;
}
