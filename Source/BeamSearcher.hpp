#ifndef BeamSearcher_hpp
#define BeamSearcher_hpp

#include "InformedSearcher.hpp"
#include <memory>
#include <map>
#include <set>
#include <utility>

#ifndef BEAM_WIDTH
	#define BEAM_WIDTH 2
#endif

using namespace std;


/**
 * Comparator that sorts nodes first by their depth, and then by heuristic cost
 */
template <class State_type>
struct BeamComparator {
	typedef shared_ptr<InformedNode<State_type>> INode_ptr;
	
	bool operator()(const INode_ptr& a, const INode_ptr& b) const
	{
		// Sort by branch depth first just like bfs
		if (a->getBranchDepth() != b->getBranchDepth())
		{
			return a->getBranchDepth() < b->getBranchDepth();
		}
		
		// Then sort by heuristic cost
		return a->getHeuristicCost() < b->getHeuristicCost();
	}
};


template <class State_type, class HValue_functor, class Success_functor = IsGoalCheck<State_type>>
class BeamSearcher : public InformedSearcher<State_type, BeamComparator<State_type>, HValue_functor, Success_functor>
{
public:
	typedef InformedSearcher<State_type, BeamComparator<State_type>, HValue_functor, Success_functor> Super;
	typedef typename Super::Node_ptr Node_ptr;
	typedef typename Super::INode_type INode_type;
	typedef typename Super::INode_ptr INode_ptr;

private:
	/** 
	 * Maps each depth to a list of nodes that appear there. Each entry in the set
	 * is a pair of its heuristic cost and then a shared_ptr to the
	 * actual node.
	 */
	map<int, multiset<pair<int, INode_ptr>>> nodeMap;
	
	
protected:
	/**
	 * Checks if there are two many nodes at the same level as node.
	 * If there are too many, will prune the one with the highest cost.
	 */
	virtual void addInformedNodeToFrontier(INode_ptr node) override
	{
		// Create a new pairing for the node
		pair<int, INode_ptr> nodePair = {node->getHeuristicCost(), node};
		
		// The location the pair would be inserted into
		typename multiset<pair<int, INode_ptr>>::iterator nodePairLoc = nodeMap[node->getBranchDepth()].upper_bound(nodePair);
		
		
		// Test the number of nodes at a certain level
		if (nodeMap.count(node->getBranchDepth()) >= BEAM_WIDTH) {
			if (nodePairLoc == nodeMap[node->getBranchDepth()].end())
			{
				// Skip the insertion of the node because it is the most costly at
				// its depth
				return;
			}
			
			// The last node in the list needs to be pruned
			nodeMap[node->getBranchDepth()].erase(nodeMap[node->getBranchDepth()].end());
		}
		
		// Add the new pair and the node
		nodeMap[node->getBranchDepth()].insert(nodePairLoc, nodePair);
		Super::addInformedNodeToFrontier(node);
	}
	
	
public:
	/**
	 * Creates a beam searcher.
	 * Turns on success prechecking.
	 */
	BeamSearcher(HValue_functor heuristicFunc = HValue_functor(), Success_functor successFunc = Success_functor()) : Super(heuristicFunc, successFunc, true)
	{
		
	}
	
	
	/**
	 * Also clears the node map
	 */
	virtual void reset() override
	{
		Super::reset();
		nodeMap.clear();
	}
	
	
	/**
	 * Returns the next node in the frontier.
	 * Will also remove the first node at that level in the node map to keep it 
	 * in sync.
	 */
	virtual Node_ptr nextInFrontier() override
	{
		Node_ptr next = Super::nextInFrontier();
		
		// Remove the first node in the map at that index
		nodeMap[next->getBranchDepth()].erase(nodeMap[next->getBranchDepth()].begin());
		
		// Check if that level is now empty and remove it
		if (nodeMap[next->getBranchDepth()].size() == 0)
		{
			nodeMap.erase(next->getBranchDepth());
		}
		
		return next;
	}
	
	
	/**
	 * Just like the BFS search, the entire tree can be checked for duplicates
	 */
	virtual bool isRepeatedState(Node_ptr newChild) const override
	{
		INode_ptr ichild = dynamic_pointer_cast<INode_type>(newChild);
		assert(ichild);
		
		// Search the tree
		if (this->tree.find(newChild) != this->tree.end())
		{
			return true;
		}
		// Check frontier
		else if (this->frontier.find(ichild) != this->frontier.end())
		{
			return true;
		}
		
		// Node could not be found
		return false;
	}
};

#endif /* BeamSearcher_hpp */
