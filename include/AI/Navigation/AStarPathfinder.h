#pragma once

#include "IPathfinder.h"

#include <functional>

using Heuristic = std::function<float(IPathfinder::Node*, IPathfinder::Node*)>;

// Use a default "as the bird flies" heuristic
inline float DefaultHeuristic(const IPathfinder::Node* current, const IPathfinder::Node* end)
{
	return glm::length(current->location - end->location);
}

class AStarPathfinder final : public IPathfinder
{
private:
	TList<Node*> m_nodes;
	Heuristic m_heuristic;

public:
	AStarPathfinder();
	AStarPathfinder(Heuristic heuristic);
	AStarPathfinder(Heuristic heuristic, const TList<Node*>& nodes);

	virtual ~AStarPathfinder() override;

public:
	virtual TList<Node*> Calculate(vec3 start, vec3 end) override;
	void AddNode(Node* node);

protected:
	[[nodiscard]] virtual TList<Node*> GetNodes() const override;

};