#ifndef _RETURNCOORDINATE_H_
#define _RETURNCOORDINATE_H_

/******************************************************************************
 Header file
 Class:        ReturnCoordinate
 
 ReturnCoordinateis a derived class of ReturnData, it represents a vectorean 
 (true/false) returned from a GP node (see Node class).
 ***************************************************************************/
using namespace std;
 #include <vector>
#include "ReturnData.h"

class ReturnCoordinate: public ReturnData
{
private:
	vector<int> data; //The data for this class 
	
	/***********************************************
	 This method sets the typeNum to be the typeid
	 of the class. 
	 ************************************************/ 
	virtual void initTypeNum(); 
	
public:
	static const int TYPENUM;
	
	ReturnCoordinate();
	virtual ~ReturnCoordinate();
	
	/************************
	 Set the data to be val 
	 ************************/
	void setData(vector<int> val);
	
	/****************************
	 Get the data of this class 
	 ****************************/
	vector<int> getData() const;
	
protected:
	
};

#endif
