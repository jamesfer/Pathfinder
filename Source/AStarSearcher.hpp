#ifndef AStarSearcher_hpp
#define AStarSearcher_hpp

#include "InformedSearcher.hpp"
#include <set>
#include <assert.h>
#include "InformedNode.hpp"


/**
 * Comparator that sorts nodes in order of the sum of their branch and heuristic 
 * costs
 */
template <class State_type>
struct AStarComparator {
	typedef shared_ptr<InformedNode<State_type>> INode_ptr;
	
	bool operator()(const INode_ptr& a, const INode_ptr& b) const
	{
		// Comparing the cost to reach this node + the expected cost to reach
		// the goal
		int aCost = a->getHeuristicCost() + a->getBranchCost();
		int bCost = b->getHeuristicCost() + b->getBranchCost();
		
		return aCost < bCost;
	}
};


template <class State_type, class HValue_functor, class Success_functor = IsGoalCheck<State_type>>
class AStarSearcher : public InformedSearcher<State_type, AStarComparator<State_type>, HValue_functor, Success_functor>
{
public:
	typedef InformedSearcher<State_type, AStarComparator<State_type>, HValue_functor, Success_functor> Super;
	
	
	AStarSearcher(HValue_functor heuristicFunc = HValue_functor(), Success_functor successFunc = Success_functor()) : Super(heuristicFunc, successFunc)
	{
		
	}
};


#endif /* AStarSearcher_hpp */
