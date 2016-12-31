#ifndef DFSSearcher_hpp
#define DFSSearcher_hpp

#include "DequeSearcher.hpp"


/**
 * The DFS searcher fetches new nodes from the back of the frontier which is 
 * the same side they were inserted on to.
 */
template <class State_type, class Success_functor = IsGoalCheck<State_type>>
class DFSSearcher : public DequeSearcher<State_type, Success_functor>
{
public:
	typedef DequeSearcher<State_type, Success_functor> Super;
	typedef typename Super::Node_ptr Node_ptr;
	typedef typename Super::Path_ptr Path_ptr;
	
	
	DFSSearcher(Success_functor successCheck = Success_functor()) : Super(successCheck)
	{
	
	}
	
	
	/**
	 * Removes elements from the back of the frontier
	 */
	virtual Node_ptr nextInFrontier() override
	{
		Node_ptr next = this->frontier.back();
		this->frontier.pop_back();
		return next;
	}
	
	
	/**
	 * To preserve the required order of puzzle actions (UP, LEFT, DOWN, RIGHT),
	 * sibling actions must be added in reverse order.
	 * 
	 * When actions are returned from the puzzle, they come in the above order,
	 * but because DFS uses a FILO structure the order must be reversed so that
	 * UP is added to the frontier last and therefore removed first.
	 */
	virtual void addToFrontier(vector<Node_ptr> nodes) override
	{
		for (typename vector<Node_ptr>::reverse_iterator it = nodes.rbegin(); it != nodes.rend(); ++it)
		{
			Super::addToFrontier(*it);
		}
	}
};

#endif /* DFSSearcher_hpp */
