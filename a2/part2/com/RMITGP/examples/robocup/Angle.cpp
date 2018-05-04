/******************************************************************************
 Definition file
 Class:        GPAngle
 Date created: 05/09/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdio> //for sprintf
#include <string>

using namespace std;

#include "Angle.h"
#include "ReturnAngle.h"

#include "GPConfig.h"

GPAngle::GPAngle(GPConfig *conf) 
             : Terminal(ReturnAngle::TYPENUM, "ang", conf),
               value((config->randomNumGenerator->randReal() * 180.0) - 179.0)
{
}

GPAngle::GPAngle(double initValue, GPConfig *conf) :
                                Terminal(ReturnAngle::TYPENUM, "ang", conf),
                                value(initValue)
{
}

GPAngle::~GPAngle()
{
}

Terminal* GPAngle::generate(const string &name, GPConfig *conf)
{
   double tmpValue;
   string tmpName("ang");
   char copy[20];

   strcpy(copy, name.c_str());

   if (name == "")
      return new GPAngle(conf);
#ifdef OLD_GCC 
   //Older versions of gcc 2.9X shipped with a c++ library which
   //had mistakes in implementation of some methods string::compare 
   //has it's parameters in the wrong order.

   else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
   else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
   {
      sscanf(copy, "ang%lf", &tmpValue);
      return new GPAngle(tmpValue, conf);
   }

   return NULL;      
}

void GPAngle::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnAngle::TYPENUM))
      throw string("GPAngle::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnAngle *>(out)->setData(value);
}

void GPAngle::print(string &s)
{
   char str[100]; 

   sprintf(str, "%s%f", getName().c_str(), value);
   s.append(str); 
}

Node* GPAngle::copy()
{
   Node *tmp = new GPAngle(value, config);

   if (tmp == NULL)
      throw string("GPAngle::copy() Error, out of memory");

   return tmp;
}
