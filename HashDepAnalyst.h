/*
 * HashDepAnalyst.h
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#ifndef HASHDEPANALYST_H_
#define HASHDEPANALYST_H_

#include "Global.h"

class HashDepAnalyst:DepAnalyst {
public:
	HashDepAnalyst(vector<Call> *nCalls);
	void solveDeps();
	void printCallDeps();
	void simulateExecution(int meanWaitTime);
	void asyncWaitAndPrint(Call *p, int meanWaitTime, deque<Call *> readyCalls, int liveCount);
	virtual ~HashDepAnalyst();
//private:
	default_random_engine rndGen;
	mutex io_mutex;
	mutex ct_mutex;
	mutex rd_mutex;
	vector<Call> *calls;
	unordered_map<int, Call *> reads;
	unordered_map<int, Call *> writes;
};

#endif /* HASHDEPANALYST_H_ */
