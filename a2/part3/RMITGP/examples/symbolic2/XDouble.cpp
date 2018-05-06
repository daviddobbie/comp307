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
double USzDouble::value = 0.0;
double UShpDouble::value = 0.0;
double MADouble::value = 0.0;
double SESzDouble::value = 0.0;
double BNDouble::value = 0.0;
double BCDouble::value = 0.0;
double NNDouble::value = 0.0;
double MDouble::value = 0.0;

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



/*             CT                 */
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


/*              USz                 */
USzDouble::USzDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "USz", conf) 
{
}
USzDouble::~USzDouble()
{
}
Terminal* USzDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new USzDouble(conf);
   if (name == "X")
      return new USzDouble(conf);
   return NULL;
}
void USzDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("USzDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* USzDouble::copy()
{
   Node *tmp = new USzDouble(config);
   if (tmp == NULL)
      throw string("USzDouble::copy() Error, out of memory");
   return tmp;
}
void USzDouble::setValue(double v)
{
   value = v;
}

/*              UShp                 */
UShpDouble::UShpDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "UShp", conf) 
{
}
UShpDouble::~UShpDouble()
{
}
Terminal* UShpDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new UShpDouble(conf);
   if (name == "X")
      return new UShpDouble(conf);
   return NULL;
}
void UShpDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("UShpDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* UShpDouble::copy()
{
   Node *tmp = new UShpDouble(config);
   if (tmp == NULL)
      throw string("UShpDouble::copy() Error, out of memory");
   return tmp;
}
void UShpDouble::setValue(double v)
{
   value = v;
}



/*              MA                 */
MADouble::MADouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "MA", conf) 
{
}
MADouble::~MADouble()
{
}
Terminal* MADouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new MADouble(conf);
   if (name == "X")
      return new MADouble(conf);
   return NULL;
}
void MADouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("MADouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* MADouble::copy()
{
   Node *tmp = new MADouble(config);
   if (tmp == NULL)
      throw string("MADouble::copy() Error, out of memory");
   return tmp;
}
void MADouble::setValue(double v)
{
   value = v;
}



/*              SESz                 */
SESzDouble::SESzDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "SESz", conf) 
{
}
SESzDouble::~SESzDouble()
{
}
Terminal* SESzDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new SESzDouble(conf);
   if (name == "X")
      return new SESzDouble(conf);
   return NULL;
}
void SESzDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("SESzDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* SESzDouble::copy()
{
   Node *tmp = new SESzDouble(config);
   if (tmp == NULL)
      throw string("SESzDouble::copy() Error, out of memory");
   return tmp;
}
void SESzDouble::setValue(double v)
{
   value = v;
}



/*              BN                */
BNDouble::BNDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "BN", conf) 
{
}
BNDouble::~BNDouble()
{
}
Terminal* BNDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new BNDouble(conf);
   if (name == "X")
      return new BNDouble(conf);
   return NULL;
}
void BNDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("BNDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* BNDouble::copy()
{
   Node *tmp = new BNDouble(config);
   if (tmp == NULL)
      throw string("BNDouble::copy() Error, out of memory");
   return tmp;
}
void BNDouble::setValue(double v)
{
   value = v;
}



/*              BC                 */
BCDouble::BCDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "BC", conf) 
{
}
BCDouble::~BCDouble()
{
}
Terminal* BCDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new BCDouble(conf);
   if (name == "X")
      return new BCDouble(conf);
   return NULL;
}
void BCDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("BCDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* BCDouble::copy()
{
   Node *tmp = new BCDouble(config);
   if (tmp == NULL)
      throw string("BCDouble::copy() Error, out of memory");
   return tmp;
}
void BCDouble::setValue(double v)
{
   value = v;
}



/*              NN                 */
NNDouble::NNDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "NN", conf) 
{
}
NNDouble::~NNDouble()
{
}
Terminal* NNDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new NNDouble(conf);
   if (name == "X")
      return new NNDouble(conf);
   return NULL;
}
void NNDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("NNDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* NNDouble::copy()
{
   Node *tmp = new NNDouble(config);
   if (tmp == NULL)
      throw string("NNDouble::copy() Error, out of memory");
   return tmp;
}
void NNDouble::setValue(double v)
{
   value = v;
}


/*              M                 */
MDouble::MDouble(GPConfig *conf) : Terminal(ReturnDouble::TYPENUM, "M", conf) 
{
}
MDouble::~MDouble()
{
}
Terminal* MDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new MDouble(conf);
   if (name == "X")
      return new MDouble(conf);
   return NULL;
}
void MDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("MDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}
Node* MDouble::copy()
{
   Node *tmp = new MDouble(config);
   if (tmp == NULL)
      throw string("MDouble::copy() Error, out of memory");
   return tmp;
}
void MDouble::setValue(double v)
{
   value = v;
}
