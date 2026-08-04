#pragma once

#include <vector>
#include <poly2tri/poly2tri.h>

#include "Maths.h"

#include "Utility/Collections/TList.h"

using std::vector;
using Poly2Point = p2t::Point;

class NavMeshObstacle
{
protected:
	TList<vec3> m_points;

private:
	vector<Poly2Point*> m_polyPoints;

public:
	NavMeshObstacle() = default;
	~NavMeshObstacle();

public:
	[[nodiscard]] vector<Poly2Point*> GetPoints();

};