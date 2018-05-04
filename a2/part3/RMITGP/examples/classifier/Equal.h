#ifndef _EQUAL_H_
#define _EQUAL_H_

/*****************************************************************************
 Header file
 Class:        Equal 
 Date created: 28/03/2006
 Written by:   Djaka W Kurniawan
 
 Equal is a function which accepts two double arguments and returns a
 boolean.
 It returns true if the first argument is equal the second argument,
 and returns false otherwise.
 *****************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class Equal : public Function
{
private:
	
public:
    Equal(GPConfig *conf);
    virtual ~Equal();
    static Function* generate(const string &name, GPConfig *conf);
    virtual void evaluate(ReturnData *out);
    virtual Node* copy();
	
protected:
};

#endif
