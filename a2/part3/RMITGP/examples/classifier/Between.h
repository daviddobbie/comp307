#ifndef _BETWEEN_H_
#define _BETWEEN_H_

/*****************************************************************************
 Header file
 Class:        Between
 Date created: 28/03/2006
 Written by:   Djaka W Kurniawan
 
 Between is a function which accepts three arguments, three doubles. 
 If the first argument is between second argument and third argument, then 
 return true, else return false.
 *****************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Between : public Function
{
private:
	
public:
    Between(GPConfig *conf);
    virtual ~Between();
    static Function* generate(const string &name, GPConfig *conf);
    virtual void evaluate(ReturnData *out);
    virtual Node* copy();
	
protected:
	
};

#endif
