#ifndef _IF_H_
#define _IF_H_

/******************************************************************************
 Header file
 Class:        If
 Date created: 15/08/2002
 Written by:   Dylan Mawhinney
 
 If is a function which accepts three arguments, a boolean and two doubles. 
 If the first argument is true the second argument is returned, otherwise
 the third argument is returned.
 ******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class If : public Function
{
private:
	
public:
	/*************
	 Constructor.
	 **************/
	If(GPConfig *conf);
	
	/*********************
	 virtual destructor
	 *********************/
	virtual ~If();
	
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
