#include <vector>
#include <iostream>
#include "Generator.hpp"

using namespace std;


void printUsage()
{
	cout << "Usage:" << endl;
	cout << "      generator <puzzleWidth> <puzzleHeight> <numOfMoves>" << endl;
	cout << endl;
	cout << "Output:" << endl;
	cout << "      A correctly formatted puzzle file including dimensions." << endl;
}


/**
 * Usage:
 *      generator <puzzleWidth> <puzzleHeight> <numOfMoves>
 *
 * Output:
 *      A correctly formatted puzzle file including dimensions.
 */
int main(int argc, const char* argv[])
{
	if (argc == 2 && strncmp(argv[1], "help", 4) == 0)
	{
		printUsage();
		return 0;
	}

	if (argc < 4)
	{
		cerr << "You did not specify enough arguments. Expected 4 got " << argc << endl;
		printUsage();
		return 1;
	}

	Generator generator{atoi(argv[3])};
	shared_ptr<Puzzle> puzzle = generator.generate(atoi(argv[1]), atoi(argv[2]));

	// Print the initial and goal puzzle in the correct form
	cout << atoi(argv[1]) << "x" << atoi(argv[2]) << endl;
	for (int i = 0; i < atoi(argv[1]) * atoi(argv[2]); ++i)
	{
		cout << puzzle->at(i) << " ";
	}
	cout << endl;
	for (int i = 0; i < atoi(argv[1]) * atoi(argv[2]); ++i)
	{
		cout << i << " ";
	}
	cout << endl;
}
