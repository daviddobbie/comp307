/******************************************************************************
 Definition file
 Class:        XDouble
 Date created: 08/06/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdlib> 
#include <cstdio> //for sprintf
#include <string>

using namespace std;

#include "XDouble.h"
#include "ReturnDouble.h"

double XDouble::value = 0.0;
double CTDouble::value = 0.0;

XDouble::XDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "X", conf) 
{
}
XDouble::~XDouble()
{
}
Terminal* XDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new XDouble(conf);
   if (name == "X")
      return new XDouble(conf);
   return NULL;
}
void XDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("XDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* XDouble::copy()
{
   Node *tmp = new XDouble(config);
   if (tmp == NULL)
      throw string("XDouble::copy() Error, out of memory");
   return tmp;
}
void XDouble::setValue(double v)
{
   value = v;
}





CTDouble::CTDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "CT", conf) 
{
}
CTDouble::~CTDouble()
{
}
Terminal* CTDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new CTDouble(conf);
   if (name == "X")
      return new CTDouble(conf);
   return NULL;
}
void CTDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("CTDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* CTDouble::copy()
{
   Node *tmp = new CTDouble(config);
   if (tmp == NULL)
      throw string("CTDouble::copy() Error, out of memory");
   return tmp;
}
void CTDouble::setValue(double v)
{
   value = v;
}
