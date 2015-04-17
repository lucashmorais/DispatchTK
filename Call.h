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

	//Pointers to Calls that this Call depends on
	unordered_set<Call *> RAWdeps;
	unordered_set<Call *> WAWdeps;
	unordered_set<Call *> WARdeps;

	//Pointers to Calls that depend on this one
	unordered_set<Call *> trueDependents;
	unordered_set<Call *> falseDependents;

	inline void addFalseDependent(Call *p)
	{
		falseDependents.insert(p);
	}

	inline void addTrueDependent(Call *p)
	{
		trueDependents.insert(p);
	}

	inline void addRAWDep(Call *p)
	{
		RAWdeps.insert(p);
		addTrueDependent(p);
	}

	inline void addWAWDep(Call *p)
	{
		WAWdeps.insert(p);
		addFalseDependent(p);
	}

	inline void addWARDep(Call *p)
	{
		WARdeps.insert(p);
		addFalseDependent(p);
	}

	inline void removeSelfReferences()
	{
		RAWdeps.erase(this);
		WAWdeps.erase(this);
		WARdeps.erase(this);
	}

	virtual ~Call();
};

#endif /* CALL_H_ */
