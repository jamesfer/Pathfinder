#ifndef GreedySearcher_hpp
#define GreedySearcher_hpp

#include "InformedSearcher.hpp"
#include "InformedNode.hpp"


/**
 * Comparator that sorts nodes in order of their heuristic cost
 */
template<class State_type>
struct GreedyHeuristicComparator
{
	typedef shared_ptr<InformedNode<State_type>> INode_ptr;
	
	bool operator()(const INode_ptr& a, const INode_ptr& b) const
	{
		return a->getHeuristicCost() < b->getHeuristicCost();
	}
};


template<class State_type, class HValue_functor, class Success_functor = IsGoalCheck<State_type>>
class GreedySearcher : public InformedSearcher<State_type, GreedyHeuristicComparator<State_type>, HValue_functor, Success_functor>
{
public:
	typedef InformedSearcher<State_type, GreedyHeuristicComparator<State_type>, HValue_functor, Success_functor> Super;
	
	
	GreedySearcher(HValue_functor heuristicFunc = HValue_functor(), Success_functor successFunc = Success_functor()) : Super(heuristicFunc, successFunc)
	{
		
	}
};

#endif /* GreedySearcher_hpp */
