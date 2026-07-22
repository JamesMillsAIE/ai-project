#include "AI/Pathfinding/IPathfinder.h"

IPathfinder::Node::Node(const float cost, const vec3 location)
	: hScore{ 0 }, gScore{ 0 }, previous{ nullptr }, cost{ cost }, location{ location }
{

}

float IPathfinder::Node::FScore() const
{
	return hScore + gScore;
}

void IPathfinder::Node::Connect(Node* endpoint, float c)
{
	connections.emplace_back(endpoint, c);
}

bool IPathfinder::NodeComparer::operator()(const Node* lhs, const Node* rhs) const
{
	return lhs->FScore() < rhs->FScore();
}

IPathfinder::Node* IPathfinder::GetClosestNode(const vec3 point) const
{
	Node* closest{ nullptr };
	float distance = FLT_MAX;

	for (Node* node : GetNodes())
	{
		if (const float dist = glm::length(point - node->location); dist < distance)
		{
			distance = dist;
			closest = node;
		}
	}

	return closest;
}
