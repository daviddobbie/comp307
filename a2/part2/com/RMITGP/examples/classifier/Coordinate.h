#ifndef _COORDINATE_H_
#define _COORDINATE_H_

/******************************************************************************
 Header file
 Class:        Coordinate
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 ******************************************************************************/

class GPConfig;

#include <string>
#include <vector>
#include "Terminal.h"

class Coordinate : public Terminal 
{
private:
	vector<int> value; //The data for this class 
	int x;
	int y;
	
public:
	Coordinate(GPConfig *conf);
	explicit Coordinate(int xp,int yp,GPConfig *conf);
	virtual ~Coordinate();
	
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
