/*
 * Call.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#include "Call.h"



Call::Call(vector<int> nReads, vector<int> nWrites, string nName) {
	//TODO: Test if copy occurs as expected
	reads = nReads;
	writes = nWrites;
	name = nName;
}

Call::~Call() {
	// TODO Auto-generated destructor stub
}

void Call::printPositionsTest()
{
	cout << "\t >> Reads:" << endl;
	for (int i = 0; i < reads.size(); i++)
	{
		cout << "\t " << reads[i];
		cout << endl;
	}
	cout << "\t >> Writes:" << endl;
	for (int i = 0; i < writes.size(); i++)
	{
		cout << "\t " << writes[i];
		cout << endl;
	}
}
