#ifndef BFSSearcher_hpp
#define BFSSearcher_hpp

#include "DequeSearcher.hpp"
#include <deque>
#include <algorithm>


/**
 * The BFS searcher pops nodes of the front of the frontier when needed.
 * It also overrides the is repeated state check to check the entire tree.
 */
template <class State_type, class Success_functor = IsGoalCheck<State_type>>
class BFSSearcher : public DequeSearcher<State_type, Success_functor>
{
public:
	typedef DequeSearcher<State_type, Success_functor> Super;
	typedef typename Super::Node_ptr Node_ptr;
	typedef typename Super::Path_ptr Path_ptr;
	
	
	BFSSearcher(Success_functor successCheck = Success_functor()) : Super(successCheck)
	{
	
	}
	
	
	/**
	 * Removes elements from the front of the frontier.
	 */
	virtual Node_ptr nextInFrontier() override
	{
		Node_ptr next = this->frontier.front();
		this->frontier.pop_front();
		return next;
	}
	
	
	/**
	 * When conducting a breadth first search, the entire tree can be checked 
	 * for duplicates
	 */
	virtual bool isRepeatedState(Node_ptr newChild) const override
	{
		// Search the tree
		if (this->tree.find(newChild) != this->tree.end())
		{
			return true;
		}
		// Search the frontier
		else if (find(this->frontier.begin(), this->frontier.end(), newChild) != this->frontier.end())
		{
			return true;
		}
		
		return false;
	}
};

#endif /* BFSSearcher_hpp */
