#ifndef _XDOUBLE_H_
#define _XDOUBLE_H_

/******************************************************************************
 Header file
 Class:        XDouble 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 XDouble is a variable terminal. 
***************************************************************************/


/*
    Note from David Dobbie, COMP 307 Assignment 2 Part 3:
        * To add on several inputs to the genetic program there are several
        * classes that are very similar. This is due to the package requiring
        * the main differentiation between inputs - what it is called - to be
        * inherited through the constructor. C++ does not allow separate constructors
        * for classes that inherit. 
*/


class GPConfig;

#include <string>
#include "Terminal.h"

class XDouble : public Terminal 
{
   private:
      static double value; //The data for this class 
   public:
      XDouble(GPConfig *conf);
      virtual ~XDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();
      static void setValue(double v);
   protected:
};



class CTDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      CTDouble(GPConfig *conf);
      virtual ~CTDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};

class USzDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      USzDouble(GPConfig *conf);
      virtual ~USzDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};

/*              UShp                 */
class UShpDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      UShpDouble(GPConfig *conf);
      virtual ~UShpDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};

/*              MA                 */
class MADouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      MADouble(GPConfig *conf);
      virtual ~MADouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};



/*              SESz                 */
class SESzDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      SESzDouble(GPConfig *conf);
      virtual ~SESzDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};


/*              BN                */
class BNDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      BNDouble(GPConfig *conf);
      virtual ~BNDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};

/*              BC                 */
class BCDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      BCDouble(GPConfig *conf);
      virtual ~BCDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};

/*              NN                 */
class NNDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      NNDouble(GPConfig *conf);
      virtual ~NNDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};

/*              M                 */
class MDouble :  public Terminal
{
   private:
      static double value; //The data for this class 
   public:
      MDouble(GPConfig *conf);
      virtual ~MDouble();
      static Terminal* generate(const string &name, GPConfig *conf);
      virtual void evaluate(ReturnData *out);  
      virtual Node* copy();
      static void setValue(double v);
   protected:
};





#endif
