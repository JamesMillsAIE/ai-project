#pragma once

#include <poly2tri/poly2tri.h>

#include "IPathfinder.h"

class AStarPathfinder;
class NavMeshObstacle;

using p2t::CDT;
using Poly2Point = p2t::Point;

class NavMesh
{
private:
	static int32 StringPull(const vec3* portals, int32 nPortals, vec3* points, int32 maxPoints);

public:
	class NavMeshNode final : public IPathfinder::Node
	{
	public:
		vec3 verticies[3];

	public:
		NavMeshNode(float c, vec3 loc);
		~NavMeshNode() override = default;

	public:
		int32 GetAdjacentVertices(NavMeshNode* other, vec3* adjacent);

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
	[[nodiscard]] TList<vec3> Calculate(vec3 start, vec3 end);

};