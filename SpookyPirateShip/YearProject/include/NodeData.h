#pragma once
#include <string>
#include <queue> //
#include "Graph.h" //
#include <SFML\Graphics.hpp>
#include "MyVector3.h"

template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;
// ---------------------------------------------------------------------
//  Name:           NodeData
//  Description:    A simple struct to encapsulate all the node data.
//                  Add or remove fields as required.               
// ---------------------------------------------------------------------
struct NodeData
{
	MyVector3 m_position;
	std::string m_name;
	bool m_isPassable{ true };
	float m_pathCost; // g(n)
	float m_distanceToGoal; // h(n)
	float m_totalEstimatedDistance; // f(n)

	sf::CircleShape m_circle;
};

// comparer for A*
template<class NodeType, class ArcType>
class NodeSearchCostComparerAstar
{
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	bool operator()(Node* n1, Node* n2)
	{
		return n1->m_data.m_totalEstimatedDistance > n2->m_data.m_totalEstimatedDistance;
	}
};

template<class NodeType, class ArcType>
class NodeSearchCostComparer
{
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	bool operator()(Node* n1, Node* n2)
	{
		return n1->m_data.m_pathCost > n2->m_data.m_pathCost;
	}
};

template <typename Data, typename Container, typename Predicate>
class MyPriorityQueue : public std::priority_queue<Data, Container, Predicate>
{
public:
	// std::priority_queue has two useful members:
	// 1. this->c is the underlying container of a priority_queue
	// 2. this->comp is the comparison predicate
	void reorder()
	{

		// std::make_heap rearranges the elements in the range [first,last] in such 
		//  a way that they form a heap.
		// std::begin() returns an iterator to the beginning of the given container c 		
		std::make_heap(std::begin(this->c), std::end(this->c), this->comp);
	}
};
