/*
 * HashDepAnalyst.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#include "Global.h"

HashDepAnalyst::HashDepAnalyst(vector<Call> *nCalls) {
	calls = nCalls;
}

HashDepAnalyst::~HashDepAnalyst() {
	// TODO Auto-generated destructor stub
}

void HashDepAnalyst::solveDeps()
{
	/*
	 * Maybe it would be possible to accelerate dependency resolution by implementing the following heuristic:
	 * >> Every time a dependency is found, temporarily remove all positions referenced by the dep from the current call.
	 * >> After all dependencies have been analyzed, add back the removed positions.
	 */
	for (unsigned int i = 0; i != calls->size(); i++)
	{
		//cout << "seeing " << i << endl;
		Call * c = &((*calls)[i]);

		//cout << "testing raw" << endl;
		for (unsigned int j = 0; j != c->reads.size(); j++)
		{
			const int &pos = c->reads[j];
			//cout << "testing pos: " << pos << endl;

			if (writes.find(pos) != writes.end())
			{
				c->addRAWDep(writes[pos]);
			}

			reads[pos] = c;
		}

		for (unsigned int j = 0; j != c->writes.size(); j++)
		{
			const int &pos = c->writes[j];

			//WAW
			if (writes.find(pos) != writes.end())
			{
				c->addWAWDep(writes[pos]);
			}

			//WAR
			if (reads.find(pos) != reads.end())
			{
				c->addWARDep(reads[pos]);
			}

			writes[pos] = c;
		}

		c->removeSelfReferences();
	}
}

void HashDepAnalyst::asyncWaitAndPrint(Call *p, int meanWaitTime, deque<Call *> readyCalls, int liveCount)
{
	ct_mutex.lock();
	liveCount++;
	ct_mutex.unlock();

	cout << "sleep time: " << meanWaitTime << "(ns)" << endl;
	normal_distribution<double> distribution(meanWaitTime, 1);

	//TODO: Do we really needs these locks here?
	mutex mtx;
	unique_lock<mutex> lck(mtx);
	condition_variable cv;

	int waitTime = (int) distribution(rndGen);

	cv.wait_for(lck, chrono::nanoseconds(waitTime));

	//Tasks depending on the just executed one are now ready for execution
	for (Call *d: p->falseDependents)
	{
		if (d->decrementDepCount())
		{
			readyCalls.push_back(d);
		}
	}
	for (Call *d: p->trueDependents)
	{
		if (d->decrementDepCount())
		{
			readyCalls.push_back(d);
		}
	}

	io_mutex.lock();
	cout << "Call " << p->name << " finished executing." << endl;
	io_mutex.unlock();
}

void HashDepAnalyst::simulateExecution(int meanWaitTime)
{
	deque<Call *> readyCalls;
	unordered_set<Call *> issuedCalls;
	vector<thread> threads;
	int liveCount = 0;

	for (Call &p: *calls)
		p.resetDepCount();

	Call *first = &((*calls)[0]);

	readyCalls.push_back(first);
	issuedCalls.insert(first);

	while (!readyCalls.empty())
	{
		Call * p = readyCalls.front();
		readyCalls.pop_front();

		threads.push_back(thread(&HashDepAnalyst::asyncWaitAndPrint, this, p, meanWaitTime, readyCalls, liveCount));
	}

	for (auto &t: threads)
		t.join();
}

void HashDepAnalyst::printCallDeps()
{
	for (auto &c: *calls)
	{
		cout << "Call " << c.name << " deps:" << endl;
		c.printDeps();
	}
}
