#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

/******************************************************************************
 Header file
 Class:        Attribute
 Date created: 12/04/2006
 Wrriten by: Djaka W Kurniawan
 
 Attribute is a derived class of terimnal, it represents a pixel in the image.
 The pixel number is determined in the construction stage.
 ******************************************************************************/

class GPConfig;

#include <string>
#include "Terminal.h"

class Attribute : public Terminal 
{
private:
	double value; //The data for this class 
	int pixel;
	
public:
	Attribute(GPConfig *conf);
	explicit Attribute(double initValue, GPConfig *conf);
	explicit Attribute(int initValue, GPConfig *conf);
	virtual ~Attribute();
	
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
