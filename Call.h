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

	int depCount = 0;

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
		p->addTrueDependent(this);
	}

	inline void addWAWDep(Call *p)
	{
		WAWdeps.insert(p);
		p->addFalseDependent(this);
	}

	inline void addWARDep(Call *p)
	{
		WARdeps.insert(p);
		p->addFalseDependent(this);
	}

	inline void removeSelfReferences()
	{
		RAWdeps.erase(this);
		WAWdeps.erase(this);
		WARdeps.erase(this);
	}

	inline bool decrementDepCount()
	{
		depCount--;
		return depCount == 0;
	}

	void resetDepCount();

	virtual ~Call();
};

#endif /* CALL_H_ */
