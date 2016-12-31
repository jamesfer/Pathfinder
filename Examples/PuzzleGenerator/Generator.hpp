#ifndef Generator_hpp
#define Generator_hpp

#include "BFSSearcher.hpp"
#include "DFSSearcher.hpp"
#include <sstream>
#include "Puzzle.hpp"


/**
 * Success functor that checks if the node has the required depth
 */
struct BranchDepthCheck
{
private:
	int goalDepth;
	
public:
	BranchDepthCheck(int goalDepth) : goalDepth(goalDepth)
	{
		
	}
	
	
	bool operator()(const Node<Puzzle>& node) const
	{
		return node.getBranchCost() >= goalDepth;
	}
};


/**
 * A DFS searcher type that starts with an ordered board with its given size 
 * and then a set number of moves on it.
 */
class Generator : public DFSSearcher<Puzzle, BranchDepthCheck>
{
public:
	typedef DFSSearcher<Puzzle, BranchDepthCheck> Super;
	
public:
	Generator(int goalDepth);
	
	/**
	 * Creates an ordered puzzle and then performs moves on it.
	 */
	shared_ptr<Puzzle> generate(int width, int height);
};

#endif /* Generator_hpp */
