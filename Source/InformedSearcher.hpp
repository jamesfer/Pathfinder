#ifndef InformedSearcher_hpp
#define InformedSearcher_hpp

#include "Searcher.hpp"
#include <assert.h>
#include "InformedNode.hpp"

using namespace std;


/**
 * Helper class that implements a multiset to store the frontier and 
 * automatically creates informed nodes and sets their heuristic estimate 
 * based on what is returned from the HValue_functor.
 */
template<class State_type, class HeuristicComparator, class HValue_functor, class Success_functor = IsGoalCheck<State_type>>
class InformedSearcher : public Searcher<State_type, Success_functor>
{
public:
	typedef Searcher<State_type, Success_functor> Super;
	typedef typename Super::State_ptr State_ptr;
	typedef typename Super::Node_ptr Node_ptr;
	typedef typename Super::Edge_ptr Edge_ptr;
	typedef typename Super::Path_ptr Path_ptr;
	typedef InformedNode<State_type> INode_type;
	typedef shared_ptr<INode_type> INode_ptr;
	
protected:
	multiset<INode_ptr, HeuristicComparator> frontier;
	
	
	/**
	 * Functor instance that is used to generate the heuristic estimates.
	 */
	HValue_functor hValueFunctor;
	
	
protected:
	/**
	 * Helper function for subclasses to remove the need to cast nodes into 
	 * informed nodes.
	 */
	virtual void addInformedNodeToFrontier(INode_ptr inode)
	{
		frontier.insert(inode);
	}
	
public:
	/**
	 * Creates an informed searcher
	 * By default turns off success prechecking.
	 */
	InformedSearcher(HValue_functor heuristicFunc = HValue_functor(), Success_functor successFunc = Success_functor(), bool precheckSuccess = false) : Super(successFunc, precheckSuccess), hValueFunctor(heuristicFunc)
	{
		
	}
	
	
	/**
	 * Creates informed nodes and assigns them a heuristic estimate.
	 */
	virtual Node_ptr makeNode(State_ptr state, Edge_ptr edge = nullptr) const override
	{
		int cost = hValueFunctor(state);
		return make_shared<INode_type>(state, cost, edge);
	}
	
	
	/**
	 * Also resets the frontier.
	 */
	virtual void reset() override
	{
		Super::reset();
		frontier.clear();
	}
	
	
	/**
	 * Returns the front element of the frontier.
	 */
	virtual Node_ptr nextInFrontier() override
	{
		Node_ptr next = *frontier.begin();
		frontier.erase(frontier.begin());
		return next;
	}
	
	
	/**
	 * Inserts the node into the sorted frontier.
	 * Asserts that the node is an informed node type
	 */
	virtual void addToFrontier(Node_ptr node) override
	{
		INode_ptr inode = dynamic_pointer_cast<INode_type>(node);
		assert(inode);
		addInformedNodeToFrontier(inode);
	}
	
	
	virtual unsigned long frontierSize() const override
	{
		return frontier.size();
	}
};

#endif /* InformedSearcher_hpp */
