#ifndef _RANDSOPERATION_H_
#define _RANDSOPERATION_H_

/******************************************************************************
 Header file
 Class:        RandSOperation
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 ******************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class RandSOperation : public Terminal 
{
private:
	enum s_operations{MED=0,AVG,STD,RANGE,OPER_END};
	int value; //The data for this class 
	
public:
	RandSOperation(GPConfig *conf);
	explicit RandSOperation(int initValue, GPConfig *conf);
	virtual ~RandSOperation();
	
	static Terminal* generate(const string &name, GPConfig *conf);
	
	virtual void evaluate(ReturnData *out);  
	virtual void print(string &s);
	
	/**********************************
	 Copies this terminal and returns
	 a pointer to the copy.
	 **********************************/
	virtual Node* copy();
protected:
	
};

#endif
