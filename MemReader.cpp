/*
 * MemReader.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#include "MemReader.h"

using namespace reading;

MemReader::MemReader(ifstream * nDump) {
	dump = nDump;
}

MemReader::~MemReader() {
	// TODO Auto-generated destructor stub
}

class MemReader::MemPosition
{
public:
	int pos;
	posType type;

	MemPosition (int nPos = -1, MemReader::posType nType = notMem)
	{
		pos = nPos;
		type = nType;
	}
};

string MemReader::readName()
{
	string name = "";
	*dump >> name;

	if (name.find(';') == string::npos)
	{
		//cout << "name: " << name << endl;
		return name;
	}
	else
	{
		//cout << "Ended!" << endl;
		*dump >> name;
		*dump >> name;
		return "";
	}
}

MemReader::MemPosition MemReader::readPosition()
{
	string aux;
	int pos = -1;
	int streamBack;
	posType type;

	streamBack = dump->tellg();

	*dump >> aux;

	//cout << "aux: " << aux << "|" << endl;

	if (!aux.compare("R:"))
	{
		*dump >> hex >> pos;
		type = read;
	}
	else if (!aux.compare("W:"))
	{
		*dump >> hex >> pos;
		type = write;
	}
	else
	{
		(*dump).seekg(streamBack);
		type = notMem;
	}

	return MemPosition(pos, type);
}

void MemReader::readDump()
{
	while (!(*dump).eof())
	{
		string name = readName();
		if (!name.compare(""))
			break;
		vector<int> reads;
		vector<int> writes;
		while(true)
		{
			MemPosition mpos = readPosition();

			if (mpos.type == notMem)
				break;
			else if (mpos.type == read)
				reads.push_back(mpos.pos);
			else
				writes.push_back(mpos.pos);
		}
		calls.push_back(Call(reads, writes, name, calls.size()));
	}
}

void MemReader::printTest()
{
	for (unsigned int i = 0; i != calls.size(); i++)
	{
		Call &c = calls[i];

		cout << "Call #" << i << ": " << c.name << endl;
		c.printPositionsTest();
	}
}

