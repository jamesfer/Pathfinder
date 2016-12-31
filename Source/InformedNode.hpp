#ifndef InformedNode_hpp
#define InformedNode_hpp

#include "Node.hpp"


/**
 * An informed node is a type of node that also stores it heuristic cost.
 * This is so the heuristic element does not have to be computed more than once.
 */
template <class State_type>
class InformedNode : public Node<State_type>
{
public:
	typedef typename Node<State_type>::State_ptr State_ptr;
	typedef typename Node<State_type>::Edge_ptr Edge_ptr;
	
private:
	int heuristicCost;
	
public:
	/**
	 * Creates a node at the given state with a heuristic estimate.
	 */
	InformedNode(State_ptr state, int heuristicCost, Edge_ptr edge = nullptr) : Node<State_type>(state, edge), heuristicCost(heuristicCost)
	{
		
	}
	
	
	/**
	 * Getter for heuristic cost
	 */
	int getHeuristicCost() const
	{
		return heuristicCost;
	}
};

#endif /* InformedNode_hpp */
