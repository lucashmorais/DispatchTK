/*
 * MemReader.h
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#ifndef MEMREADER_H_
#define MEMREADER_H_

#include <vector>
#include "Call.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace reading
{
	using namespace std;

	class MemReader {
	public:
		MemReader(ifstream * nDump);
		virtual ~MemReader();
		void readDump();
		void printTest();
		enum posType{read, write, notMem};
		class MemPosition;
	private:
		ifstream * dump;
		string readName();
		MemPosition readPosition();
		vector<Call> calls;
	};
}

#endif /* MEMREADER_H_ */
