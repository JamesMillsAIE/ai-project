#pragma once

#include "IPathfinder.h"

#include <functional>

using Heuristic = std::function<float(IPathfinder::Node*, IPathfinder::Node*)>;

class AStarPathfinder final : public IPathfinder
{
private:
	vector<Node*> m_nodes;
	Heuristic m_heuristic;

public:
	AStarPathfinder();
	AStarPathfinder(Heuristic  heuristic);
	AStarPathfinder(Heuristic heuristic, const vector<Node*>& nodes);

	virtual ~AStarPathfinder() override;

public:
	virtual vector<vec3> Calculate(vec3 start, vec3 end) override;
	void AddNode(Node* node);

protected:
	[[nodiscard]] virtual vector<Node*> GetNodes() const override;

};