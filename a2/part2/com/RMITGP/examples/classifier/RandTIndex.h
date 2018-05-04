#ifndef _RANDTINDEX_H_
#define _RANDTINDEX_H_

/******************************************************************************
 Header file
 Class:        RandTIndex
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 ******************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class RandTIndex : public Terminal 
{
private:
	int value; //The data for this class 
	
public:
	RandTIndex(GPConfig *conf);
	explicit RandTIndex(int initValue, GPConfig *conf);
	virtual ~RandTIndex();
	
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
