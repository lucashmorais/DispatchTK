/*
 * HashDepAnalyst.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#include "HashDepAnalyst.h"

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
			int &pos = c->reads[j];
			//cout << "testing pos: " << pos << endl;

			if (writes.find(pos) != writes.end())
			{
				c->RAWdeps.insert(writes[pos]);
			}

			reads[pos] = c;
		}

		for (unsigned int j = 0; j != c->writes.size(); j++)
		{
			int &pos = c->writes[j];

			//WAW
			if (writes.find(pos) != writes.end())
			{
				c->WAWdeps.insert(writes[pos]);
			}

			//WAR
			if (reads.find(pos) != reads.end())
			{
				c->WARdeps.insert(reads[pos]);
			}

			writes[pos] = c;
		}

		c->removeSelfReferences();
	}
}

void HashDepAnalyst::printCallDeps()
{
	for (auto &c: *calls)
	{
		cout << "Call " << c.name << " deps:" << endl;
		c.printDeps();
	}
}
