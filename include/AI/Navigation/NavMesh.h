#pragma once

#include <poly2tri/poly2tri.h>

#include "IPathfinder.h"

class AStarPathfinder;
class NavMeshObstacle;

using p2t::CDT;
using Poly2Point = p2t::Point;

class NavMesh
{
public:
	class NavMeshNode final : public IPathfinder::Node
	{
	public:
		vec3 verticies[3];

	public:
		NavMeshNode(float cost, vec3 location);
		~NavMeshNode() override = default;

	public:
		[[nodiscard]] int GetAdjacentVertices(NavMeshNode* other, vec3* adjacent);

	};

private:
	TList<NavMeshObstacle*> m_obstacles;
	CDT* m_ctd;
	TList<vec3> m_meshPoints;

	vector<Poly2Point*> m_meshPolyPoints;
	AStarPathfinder* m_pathfinder;

public:
	NavMesh();
	~NavMesh();

public:
	void Build();

private:
	[[nodiscard]] vector<Poly2Point*> PolyPoints() const;

};