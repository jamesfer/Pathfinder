#include <iostream>
#include "WoodenPuzzle.hpp"
#include "SearchRunner.hpp"


void printUsage()
{
	cout << "Usage:" << endl;
	cout << "      wooden-solitaire <searchMethod>" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "      searchMethod      One of BFS, DFS, GBFS, AS, CUS1 or CUS2" << endl;
	cout << endl;
	cout << "Output:" << endl;
	cout << "      <searchMethod> <nodeCount> <moves>" << endl;
}


/**
 * Usage:
 *      wooden-solitaire <searchMethod>
 *
 * Options:
 *      searchMethod      One of BFS, DFS, GBFS, AS, CUS1 or CUS2
 *                        If none is supplied defaults to DFS which is the
 *					              fastest option.
 *
 *
 * Output:
 *      <searchMethod> <nodeCount> <moves>
 */
int main(int argc, const char * argv[]) {
	string searchName;

	if (argc == 2 && strncmp(argv[1], "help", 4) == 0)
	{
		printUsage();
		return 0;
	}

	if (argc < 2)
	{
		cout << "No search method given. Defaulting to using DFS" << endl;
		searchName = "DFS";
	}
	else
	{
		searchName = string(argv[1]);
	}


	WoodenPuzzle initial;

	// Perform the search
	SearchRunner<WoodenPuzzle, WoodenPuzzle::PiecesRemainingHeuristic, WoodenPuzzle::SuccessCheck> runner;
	runner.search(initial, searchName);
}
