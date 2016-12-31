#include "Generator.hpp"


Generator::Generator(int goalDepth) : Super(BranchDepthCheck(goalDepth))	{
	
}


shared_ptr<Puzzle> Generator::generate(int width, int height)
{
	Puzzle initial = Puzzle(width, height);
	
	// Populate initial state
	stringstream boardString;
	for (int i = 0; i < width * height; ++i)
	{
		boardString << i << " ";
	}
	boardString >> initial;
	
	Path_ptr path = search(initial);
	
	// The first node in the path is the deepest child
	return (*path)[0]->getState();
}
