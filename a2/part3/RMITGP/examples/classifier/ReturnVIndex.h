#ifndef _RETURNVINDEX_H_
#define _RETURNVINDEX_H_

/******************************************************************************
 Header file
 Class:        ReturnVIndex
 Date created: 15/11/2011
 Written by:   Feng Xie
 
 ***************************************************************************/

#include "ReturnData.h"

class ReturnVIndex : public ReturnData
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
	
	ReturnVIndex();
	virtual ~ReturnVIndex();
	
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
