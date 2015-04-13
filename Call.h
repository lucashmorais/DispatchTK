/*
 * Call.h
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#ifndef CALL_H_
#define CALL_H_

#include <iostream>
#include <vector>

using namespace std;

class Call {
public:
	string name;
	Call(vector<int> nReads, vector<int> nWrites, string name);
	void printPositionsTest();
	virtual ~Call();
private:
	vector<int> reads;
	vector<int> writes;
};

#endif /* CALL_H_ */
