#pragma once

#include <vector>

#include "Maths.h"
#include "Utility/Collections/TList.h"

using std::vector;

class IPathfinder
{
public:
	class Node;

	struct Edge
	{
		Node* endpoint;
		float cost;
	};

	class Node
	{
	public:
		float hScore;
		float gScore;
		Node* previous;

		float cost;
		vec3 location;

		TList<Edge> connections;

	public:
		Node(float cost, vec3 location);
		virtual ~Node() = default;

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
	virtual TList<vec3> Calculate(vec3 start, vec3 end) = 0;

protected:
	[[nodiscard]] virtual Node* GetClosestNode(vec3 point) const;
	[[nodiscard]] virtual TList<Node*> GetNodes() const = 0;

};
