#ifndef _RECT_H_
#define _RECT_H_

/******************************************************************************
 Header file
 Class:        Rect
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 ******************************************************************************/

class GPConfig;

#include <string>
#include <vector>
#include "Terminal.h"

class Rect : public Terminal 
{
private:
	//enum rect_types{POR = 10,NUM,TYPE_END};
	vector<int> value; //The data for this class 
	//int rect_type;
	int w;
	int h;
	
public:
	Rect(GPConfig *conf);
	explicit Rect(int wp,int hp,GPConfig *conf);
	virtual ~Rect();
	
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
