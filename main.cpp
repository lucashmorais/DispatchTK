#include <iostream>
#include <fstream>
#include <string>
#include "MemReader.h"

using namespace std;
using namespace reading;

int main (int argc, char ** argv)
{
	ifstream input;

	cout << "zero: " << argv[0] << endl;
	cout << "one: " << argv[1] << endl;

	input.open(argv[1]);

	MemReader reader(&input);

	reader.readDump();

	reader.printTest();

	return 0;
}
