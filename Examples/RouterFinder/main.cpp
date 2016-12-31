#include <iostream>
#include <map>
#include <memory>
#include <fstream>
#include "City.hpp"
#include "TravelTo.hpp"
#include "SearchRunner.hpp"

using namespace std;

#define CHAR_SEPERATOR '&'


/**
 * Hash of all cities paired with their name for easy lookup
 */
map<string, shared_ptr<City>> cities;


void printUsage()
{
	cout << "Usage:" << endl;
	cout << "      router <dataFile> <searchMethod>" << endl;
	cout << endl;
	cout << "Example:" << endl;
	cout << "      Win:   router \"Inputs\\australia.txt\" CUS1" << endl;
	cout << "      Unix:  router \"Inputs/australia.txt\" CUS1" << endl;
	cout << "   Can be used when the current directory is the root of the library." << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "      dataFile          Path to a data file that represents the environment." << endl;
	cout << "                        Expected to be in the form matching the example in" << endl;
	cout << "                        RouteFinder/Inputs." << endl;
	cout << "                        The first chunk of lines follow the format:" << endl;
	cout << "                          cityName cityXCoord cityYCoord." << endl;
	cout << "                        After the separating character, the lines represent" << endl;
	cout << "                        paths between cities and are in the form:" << endl;
	cout << "                          startCityName finishCityName distanceOfPath." << endl;
	cout << "      searchMethod      One of BFS, DFS, GBFS, AS, CUS1 or CUS2" << endl;
	cout << "                        If none is supplied defaults to DFS which is the" << endl;
	cout << "                        fastest option." << endl;
	cout << endl;
	cout << "Output:" << endl;
	cout << "      <dataFile> <searchMethod> <nodeCount> <actions>" << endl;
}


/**
 * Usage:
 *      router <dataFile> <searchMethod>
 * Example:
 *      Win:   router ".\RouteFinder\Inputs\australia.txt" CUS1
 *      *nix:  router "./RouteFinder/Inputs/australia.txt" CUS1
 *  Can be used when the current directory is the root of the library.
 *
 * Options:
 *      dataFile          Path to a data file that represents the environment.
 *                        Expected to be in the form matching the example in
 *                        RouteFinder/Inputs.
 *                        The first chunk of lines follow the format:
 *                            cityName cityXCoord cityYCoord.
 *                        After the separating character, the lines represent
 *                        paths between cities and are in the form:
 *                            startCityName finishCityName distanceOfPath.
 *      searchMethod      One of BFS, DFS, GBFS, AS, CUS1 or CUS2
 *                        If none is supplied defaults to DFS which is the
 *					      fastest option.
 *
 *
 * Output:
 *      <dataFile> <searchMethod> <nodeCount> <actions>
 */
int main(int argc, const char * argv[]) {
	if (argc == 2 && strncmp(argv[1], "help", 4) == 0)
	{
		printUsage();
		return 0;
	}
	
	if (argc < 3)
	{
		cerr << "Did not provide enough arguments. Expected 3 got " << argc << endl;
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


	// Read in the list of cities
	while (inputFile.peek() != CHAR_SEPERATOR)
	{
		City newCity;
		inputFile >> newCity;
		cities[newCity.getName()] = make_shared<City>(newCity);

		// Skip all the white space inbetween names
		inputFile >> ws;
	}

	// Get the seperator character
	inputFile.get();

	// Read in all routes
	while (inputFile.peek() != EOF)
	{
		string a;
		string b;
		float distance;
		inputFile >> a;
		inputFile >> b;
		inputFile >> distance;

		// Ignore all white space
		inputFile >> ws;

		TravelTo::createRoadBetween(cities.at(a), cities.at(b), distance);
	}


	const City& initial = *cities["Darwin"];
	const City& goal = *cities["Melbourne"];

	// Search for a route
	SearchRunner<City, City::StraightLineDistanceHeuristic> runner{City::StraightLineDistanceHeuristic(goal)};
	cout << argv[1] << " ";
	runner.search(initial, goal, argv[2]);
}
