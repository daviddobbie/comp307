#include "Data.h"

double Data::max;
double Data::scale;
double Data::threshold;

Data::Data() :
   value(0),
   pos(0),
   neg(0)
{}

Data::Data(double value, double pos, double neg) :
   value(value),
   pos(pos),
   neg(neg)
{}

void Data::setVal(double val)
{
   value = val;
}

void Data::setPos(double val)
{
   pos = val;
}

void Data::setNeg(double val)
{
   neg = val;
}

void Data::incrementPos()
{
   pos++;
}

void Data::incrementNeg()
{
   neg++;
}

double Data::getVal()
{
   return value;
}

double Data::getPos()
{
   return pos;
}

double Data::getNeg()
{
   return neg;
}

ostream& operator<<(ostream& os, Data &data)
{
   double value = data.pos - data.neg;
   if (value <= Data::threshold)
      //value = Data::scale;
      value = 0;
   else
   {
      value = value / Data::max * Data::scale;
      //value = Data::scale - value;
   }
   os << round(value);
   return os;
}

istringstream& operator>>(istringstream& iss, Data &data)
{
   iss >> data.value;
   iss >> data.pos;
   iss >> data.neg;
   return iss;
}
