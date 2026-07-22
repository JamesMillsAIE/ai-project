#include "AI/Pathfinding/AStarPathfinder.h"

#include <algorithm>
#include <ranges>
#include <set>
#include <stdexcept>
#include <utility>

using std::runtime_error;
using std::set;

// Use a default "as the bird flies" heuristic
float DefaultHeuristic(const AStarPathfinder::Node* current, const AStarPathfinder::Node* end)
{
	return glm::length(current->location - end->location);
}

AStarPathfinder::AStarPathfinder()
	: m_heuristic{ DefaultHeuristic }
{

}

AStarPathfinder::AStarPathfinder(Heuristic heuristic)
	: m_heuristic{ std::move(heuristic) } { }

AStarPathfinder::AStarPathfinder(Heuristic heuristic, const vector<Node*>& nodes)
	: m_nodes{ nodes }, m_heuristic{ std::move(heuristic) } { }

AStarPathfinder::~AStarPathfinder()
{
	for (const Node* node : m_nodes)
	{
		delete node;
	}

	m_nodes.clear();
}

vector<vec3> AStarPathfinder::Calculate(const vec3 start, const vec3 end)
{
	// Get the start and end nodes
	Node* startNode = GetClosestNode(start),* endNode = GetClosestNode(end);

	// If either are nullptr, we have a problem
	if (startNode == nullptr || endNode == nullptr)
	{
		throw runtime_error("Start or end node invalid!");
	}

	// If the nodes are the same, it is an empty path (start is the end)
	if (startNode == endNode)
	{
		return { };
	}

	// Reset the start and end node values
	startNode->gScore   = startNode->hScore = 0;
	startNode->previous = nullptr;

	endNode->gScore   = endNode->hScore = 0;
	endNode->previous = nullptr;

	set<Node*, NodeComparer> openList = { startNode };
	vector<Node*> closedList;

	while (!openList.empty())
	{
		// Move the first node in the open list to the closed list
		Node* current = *openList.begin();
		openList.erase(openList.begin());
		closedList.emplace_back(current);

		// We found a valid path
		if (current == endNode)
		{
			break;
		}

		// Iterate over every connection with a node that isn't in the closed list
		for (const auto [endpoint, cost] : current->connections | std::ranges::views::filter([closedList](const Edge e)
		{
			return std::ranges::find(closedList, e.endpoint) != closedList.end();
		}))
		{
			const float gScore = current->gScore + cost;
			const float hScore = m_heuristic(endpoint, endNode);
			const float fScore = hScore + gScore;

			// We haven't visited the node
			if (std::ranges::find(openList, endpoint) == openList.end())
			{
				endpoint->gScore = gScore;
				endpoint->hScore = hScore;
				endpoint->previous = current;
				openList.insert(endpoint);
			}
			// The node is already in the open list, but the cost is cheaper
			else if (fScore < endpoint->FScore())
			{
				endpoint->gScore = gScore;
				endpoint->hScore = hScore;
				endpoint->previous = current;
			}
		}
	}

	// Calculate the path in reverse
	Node* current = endNode;
	vector<vec3> path;
	while (current != nullptr)
	{
		path.emplace_back(current->location);
		current = current->previous;
	}

	// Flip the path vector
	std::ranges::reverse(path);
	return path;
}

void AStarPathfinder::AddNode(Node* node)
{
	m_nodes.emplace_back(node);
}

vector<IPathfinder::Node*> AStarPathfinder::GetNodes() const
{
	return m_nodes;
}
