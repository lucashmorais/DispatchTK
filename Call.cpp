/*
 * Call.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#include "Global.h"

Call::Call(vector<int> nReads, vector<int> nWrites, string nName, int index) {
	ostringstream out;
	out << nName << "_" << index;
	name = out.str();
	reads = nReads;
	writes = nWrites;
	distribution = nullptr;
}

Call::~Call() {
	// TODO Auto-generated destructor stub
}

void Call::printPositionsTest()
{
	cout << "\t >> Reads:" << endl;
	for (unsigned int i = 0; i != reads.size(); i++)
	{
		cout << "\t " << reads[i];
		cout << endl;
	}
	cout << "\t >> Writes:" << endl;
	for (unsigned int i = 0; i != writes.size(); i++)
	{
		cout << "\t " << writes[i];
		cout << endl;
	}
}

void Call::printDeps()
{
	cout << "\t >> RAW:" << endl;
	for (auto i: RAWdeps)
	{
		cout << "\t" << i->name << endl;
	}

	cout << "\t >> WAW:" << endl;
	for (auto i: WAWdeps)
	{
		cout << "\t" << i->name << endl;
	}

	cout << "\t >> WAR:" << endl;
	for (auto i: WARdeps)
	{
		cout << "\t" << i->name << endl;
	}
}

double Call::simulate()
{
	int waitTime = (int) (*distribution)(rndGen);
	cv.wait_for(lck, chrono::nanoseconds(waitTime));
	int expectedWaitTime = waitTime;

	for (Call *d: wawDependents)
	{
		expectedWaitTime += d->resolveDependency(distribution);
	}

	for (Call *d: warDependents)
	{
		expectedWaitTime += d->resolveDependency(distribution);
	}

	for (Call *d: trueDependents)
	{
		expectedWaitTime += d->resolveDependency(distribution);
	}

	io_mutex.lock();
	cout << "Call " << name << " finished executing." << endl;
	io_mutex.unlock();

	return expectedWaitTime;
}

void Call::resetDepCount()
{
	depCount = RAWdeps.size() + WAWdeps.size() + WARdeps.size();
}
