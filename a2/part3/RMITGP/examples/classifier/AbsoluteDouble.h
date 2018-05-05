#ifndef _ABSOLUTEDOUBLE_H_
#define _ABSOLUTEDOUBLE_H_

/******************************************************************************
 Header file
 Class:        AbsoluteDouble 

 ******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class AbsoluteDouble : public Function
{
private:
	
public:
	/*************
	 Constructor.
	 **************/
	AbsoluteDouble(GPConfig *conf);
	
	/*********************
	 virtual destructor
	 *********************/
	virtual ~AbsoluteDouble();
	
	static Function* generate(const string &name, GPConfig *conf);
	
	/********************
	 Evaluate function
	 ********************/
	virtual void evaluate(ReturnData *out);
	
	/***********************************
	 Copies this function and it's 
	 arguments and returns a pointer to
	 the new copy.
	 ***********************************/
	virtual Node* copy();
	
protected:
	
};

#endif
