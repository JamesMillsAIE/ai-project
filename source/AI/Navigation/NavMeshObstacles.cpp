#include "AI/Navigation/NavMeshObstacles.h"

NavMeshObstacle::~NavMeshObstacle()
{
	for (const Poly2Point* point : m_polyPoints)
	{
		delete point;
	}

	m_polyPoints.clear();
}

vector<Poly2Point*> NavMeshObstacle::GetPoints()
{
	// If we have populated the points already, clean them up
	if (!m_polyPoints.empty())
	{
		for (const Poly2Point* point : m_polyPoints)
		{
			delete point;
		}

		m_polyPoints.clear();
	}

	// Fill out the new array
	m_polyPoints.resize(m_points.Count());
	for (int64 i = 0; i < static_cast<int64>(m_polyPoints.size()); ++i)
	{
		m_polyPoints[i] = new Poly2Point{ m_points[i].x, m_points[i].y };
	}

	return m_polyPoints;
}
