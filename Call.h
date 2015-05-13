/*
 * Call.h
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#ifndef CALL_H_
#define CALL_H_

using namespace std;

extern default_random_engine rndGen;
extern mutex io_mutex;
extern mutex ct_mutex;
extern mutex rd_mutex;
extern condition_variable cv;
extern mutex mtx;
extern unique_lock<mutex> lck;

class Call {
public:
	string name;
	Call(vector<int> nReads, vector<int> nWrites, string baseName, int index);
	void printPositionsTest();
	void printDeps();
	vector<int> reads;
	vector<int> writes;
	normal_distribution<double>* distribution = nullptr;

	//Pointers to Calls that this Call depends on
	unordered_set<Call *> RAWdeps;
	unordered_set<Call *> WAWdeps;
	unordered_set<Call *> WARdeps;

	int depCount = 0;

	//Pointers to Calls that depend on this one
	unordered_set<Call *> trueDependents;
	unordered_set<Call *> wawDependents;
	unordered_set<Call *> warDependents;

	inline void addWAWDependent(Call *p)
	{
		if (p != this)
			wawDependents.insert(p);
	}

	inline void addWARDependent(Call *p)
	{
		if (p != this)
			warDependents.insert(p);
	}

	inline void addTrueDependent(Call *p)
	{
		if (p != this)
			trueDependents.insert(p);
	}

	inline void addRAWDep(Call *p)
	{
		if (p != this)
		{
			//cout << name << " raw depends of " << p->name << endl;
			RAWdeps.insert(p);
			p->addTrueDependent(this);
		}
	}

	inline void addWAWDep(Call *p)
	{
		if (p != this)
		{
			//cout << name << " waw depends of " << p->name << endl;
			WAWdeps.insert(p);
			p->addWAWDependent(this);
		}
	}

	inline void addWARDep(Call *p)
	{
		if (p != this)
		{
			//cout << name << " war depends of " << p->name << endl;
			WARdeps.insert(p);
			p->addWARDependent(this);
		}
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

	inline double resolveDependency(normal_distribution<double>* nDist)
	{
		depCount--;
		cout << name << " is left with " << depCount << " deps." << endl;
		if (depCount == 0)
		{
			setupDistribution(nDist);
			auto future = async(&Call::simulate, this);
			return future.get();
		}

		return 0;
	}

	inline void setupDistribution(normal_distribution<double>* p)
	{
		distribution = p;
	}

	double simulate();
	void resetDepCount();


	virtual ~Call();
};

#endif /* CALL_H_ */
