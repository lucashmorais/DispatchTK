#include "Global.h"

using namespace std;
using namespace reading;

void testSet()
{
	unordered_set<int> set;

	set.insert(1);
	set.insert(2);
	set.insert(1);

	for (auto &i: set)
		cout << i << endl;
}

int main (int argc, char ** argv)
{
	ifstream input;

	cout << "zero: " << argv[0] << endl;
	cout << "one: " << argv[1] << endl;

	input.open(argv[1]);

	MemReader reader(&input);

	//cout << "### READER TEST ###" << endl;
	reader.readDump();
	//reader.printTest();

	cout << endl;

	//cout << "### DepAnalyst TEST ###" << endl;
	HashDepAnalyst al(&reader.calls);
	al.solveDeps();
	//al.printCallDeps();

	cout << "### Execution Simulation TEST ###" << endl;
	al.simulateExecution(1000000000);

	//cout << "### SET TESET ###" << endl;
	//testSet();

	return 0;
}
