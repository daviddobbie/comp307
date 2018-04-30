#ifndef _RETURNTOPERATION_H_
#define _RETURNTOPERATION_H_

/******************************************************************************
 Header file
 Class:        ReturnTOperation
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 ***************************************************************************/

#include "ReturnData.h"

class ReturnTOperation : public ReturnData
{
private:	  
	int data; //The data for this class 
	
	/***********************************************
	 This method sets the typeNum to be the typeid
	 of the class. 
	 ************************************************/ 
	virtual void initTypeNum(); 
	
public:
	static const int TYPENUM;
	
	ReturnTOperation();
	virtual ~ReturnTOperation();
	
	/************************
	 Set the data to be num
	 ************************/
	void setData(int num);
	
	/****************************
	 Get the data of this class 
	 ****************************/
	int getData() const;
	
protected:
	
};

#endif
