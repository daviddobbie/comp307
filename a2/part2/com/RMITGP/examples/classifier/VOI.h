#ifndef _VOI_H_
#define _VOI_H_

/******************************************************************************
 
 ******************************************************************************/

class GPConfig;


using namespace std;
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <algorithm>

#include "GPConfig.h"
#include "Function.h"
#include "ReturnDouble.h"

#include "ReturnSOperation.h"
#include "ReturnVIndex.h"

class VOI : public Function
{
private:
	enum s_operations{MED=0,AVG,STD,RANGE,OPER_END};
	vector<double> selected_points;
	
public:
	
	VOI(GPConfig *conf);
	virtual ~VOI();
	
	static Function* generate(const string &name, GPConfig *conf);
	
	virtual void evaluate(ReturnData *out);  
	
	/**********************************
	 Copies this terminal and returns
	 a pointer to the copy.
	 **********************************/
	virtual Node* copy();
	std::string itoa(int value, int base);
protected:
	
};

#endif
