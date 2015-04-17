/*
 * MemReader.h
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#ifndef MEMREADER_H_
#define MEMREADER_H_

#include "Global.h"

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
		ifstream * dump;
		string readName();
		MemPosition readPosition();
		vector<Call> calls;
	};
}

#endif /* MEMREADER_H_ */
