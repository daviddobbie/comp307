#ifndef _RANDINT_H_
#define _RANDINT_H_

/******************************************************************************
 Header file
 Class:        RandInt
 Date created: 21/03/2002
 Written by:   Dylan Mawhinney
 Modified on: 28/03/2006
 Modified by: Djaka W Kurniawan
 
 RandInt is a derived class of terminal, it represents a random double 
 valued terminal. It's value is determined at time of construction.
 Modified to generate random double between -1 and 1 
 ******************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class RandInt : public Terminal 
{
private:
	int value; //The data for this class 
	
public:
	RandInt(GPConfig *conf);
	explicit RandInt(int initValue, GPConfig *conf);
	virtual ~RandInt();
	
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
