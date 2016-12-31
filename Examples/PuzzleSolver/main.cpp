#include <iostream>
#include <fstream>
#include "Puzzle.hpp"
#include "SearchRunner.hpp"


void printUsage()
{
	cout << "Usage:" << endl;
	cout << "      search <filename> <searchMethod>" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "      searchMethod      One of BFS, DFS, GBFS, AS, CUS1 or CUS2" << endl;
	cout << endl;
	cout << "Output:" << endl;
	cout << "      <filename> <searchMethod> <nodeCount> <path>" << endl;
}


int main(int argc, const char* argv[])
{
	if (argc == 2 && strncmp(argv[1], "help", 4) == 0)
	{
		printUsage();
		return 0;
	}

	if (argc < 3)
	{
		cerr << "Did not provide enough arguments. Expected at least 3 got " << argc << endl;
		printUsage();
		return 1;
	}


	// Open the input file
	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cerr << "Could not open file: " << argv[1];
		return 2;
	}


	// Read the dimensions of the puzzles
	unsigned short width, height;
	Puzzle::extractDimensions(inputFile, width, height);

	// Read the puzzles
	Puzzle initial(width, height), goal(width, height);
	inputFile >> initial >> goal;

	// Perform the search
	SearchRunner<Puzzle, Puzzle::ManhattanDistanceHeuristic> runner{Puzzle::ManhattanDistanceHeuristic(&goal)};
	for (int i = 2; i < argc; i++)
	{
		// Output the file name
		cout << argv[1] << " ";
		runner.search(initial, goal, argv[i]);
	}
}
