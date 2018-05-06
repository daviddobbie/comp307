#ifndef _RANDVINDEX_H_
#define _RANDVINDEX_H_

/******************************************************************************
 Header file
 Class:        RandVIndex
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 ******************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class RandVIndex : public Terminal 
{
private:
	int value; //The data for this class 
	
public:
	RandVIndex(GPConfig *conf);
	explicit RandVIndex(int initValue, GPConfig *conf);
	virtual ~RandVIndex();
	
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
