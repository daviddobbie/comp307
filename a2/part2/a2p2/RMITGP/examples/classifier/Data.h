#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;
class Data
{
   private :
      double value;
      double pos;
      double neg;
   public :
      static double max;
      static double scale;
      static double threshold;
      Data();
      Data(double value, double pos, double neg);
      void setVal(double val);
      void setPos(double pos);
      void setNeg(double neg);
      void incrementPos();
      void incrementNeg();
      double getVal();
      double getPos();
      double getNeg();
      friend ostream& operator<<(ostream& os, Data &data);
      friend istringstream& operator>>(istringstream& iss, Data &data);
};
#endif
