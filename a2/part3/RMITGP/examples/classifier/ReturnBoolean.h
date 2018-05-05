#ifndef _RETURNBOOLEAN_H_
#define _RETURNBOOLEAN_H_

/******************************************************************************
 Header file
 Class:        ReturnBoolean
 Date created: 15/08/2002
 Written by:   Dylan Mawhinney
 
 ReturnBoolean is a derived class of ReturnData, it represents a boolean 
 (true/false) returned from a GP node (see Node class).
 ***************************************************************************/

#include "ReturnData.h"

class ReturnBoolean : public ReturnData
{
private:
	bool data; //The data for this class 
	
	/***********************************************
	 This method sets the typeNum to be the typeid
	 of the class. 
	 ************************************************/ 
	virtual void initTypeNum(); 
	
public:
	static const int TYPENUM;
	
	ReturnBoolean();
	virtual ~ReturnBoolean();
	
	/************************
	 Set the data to be val 
	 ************************/
	void setData(bool val);
	
	/****************************
	 Get the data of this class 
	 ****************************/
	bool getData() const;
	
protected:
	
};

#endif
