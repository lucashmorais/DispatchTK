/*
 * Call.h
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#ifndef CALL_H_
#define CALL_H_

using namespace std;

class Call {
public:
	string name;
	Call(vector<int> nReads, vector<int> nWrites, string baseName, int index);
	void printPositionsTest();
	void printDeps();
	vector<int> reads;
	vector<int> writes;
	unordered_set<Call *> RAWdeps;
	unordered_set<Call *> WAWdeps;
	unordered_set<Call *> WARdeps;
	void removeSelfReferences();
	virtual ~Call();
};

#endif /* CALL_H_ */
