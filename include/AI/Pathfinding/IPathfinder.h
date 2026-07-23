#pragma once

#include <vector>

#include "Maths.h"

using std::vector;

class IPathfinder
{
public:
	struct Node;

	struct Edge
	{
		Node* endpoint;
		float cost;
	};

	struct Node
	{
	public:
		float hScore;
		float gScore;
		Node* previous;

		float cost;
		vec3 location;

		vector<Edge> connections;

	public:
		Node(float cost, vec3 location);

	public:
		[[nodiscard]] float FScore() const;

		void Connect(Node* endpoint, float c = 1);
	};

	struct NodeComparer
	{
		bool operator()(const Node* lhs, const Node* rhs) const;
	};

public:
	IPathfinder() = default;
	virtual ~IPathfinder() = default;

public:
	virtual vector<vec3> Calculate(vec3 start, vec3 end) = 0;

protected:
	[[nodiscard]] virtual Node* GetClosestNode(vec3 point) const;

private:
	[[nodiscard]] virtual vector<Node*> GetNodes() const = 0;

};
