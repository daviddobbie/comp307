#ifndef _DIFF_H_
#define _DIFF_H_

/******************************************************************************
 
 ******************************************************************************/

class GPConfig;


using namespace std;
#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>


#include "GPConfig.h"
#include "ReturnDouble.h"
#include "Function.h"

class Diff : public Function 
{
private:
	double last_value;
	bool first;
	
public:
	
	Diff(GPConfig *conf);
	virtual ~Diff();
	
	static Function* generate(const string &name, GPConfig *conf);
	
	virtual void evaluate(ReturnData *out);  
	
	/**********************************
	 Copies this terminal and returns
	 a pointer to the copy.
	 **********************************/
	virtual Node* copy();

protected:
	
};

#endif
