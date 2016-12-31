#ifndef DequeSearcher_hpp
#define DequeSearcher_hpp

#include "Searcher.hpp"
#include <deque>


/**
 * Utility class that implements a deque as the frontier structure.
 * Does not implement the nextInFrontier method as it depends on the 
 * search strategy
 */
template <class State_type, class Success_functor = IsGoalCheck<State_type>>
class DequeSearcher : public Searcher<State_type, Success_functor>
{
public:
	typedef Searcher<State_type, Success_functor> Super;
	typedef typename Super::Node_ptr Node_ptr;
	typedef typename Super::Path_ptr Path_ptr;
	
protected:
	deque<Node_ptr> frontier;
	
public:
	DequeSearcher(Success_functor functor = Success_functor()) : Super(functor)
	{
		
	}
	
	
	virtual ~DequeSearcher()
	{
		
	}
	
	
	/**
	 * Overrides to also clear the frontier
	 */
	virtual void reset() override
	{
		Super::reset();
		frontier.clear();
	}
	
	
	/**
	 * Adds a node to the frontier
	 */
	virtual void addToFrontier(Node_ptr node) override
	{
		frontier.push_back(node);
	}
	
	
	/**
	 * Returns the size of the frontier
	 */
	virtual unsigned long frontierSize() const override
	{
		return frontier.size();
	}
};

#endif /* DequeSearcher_hpp */
