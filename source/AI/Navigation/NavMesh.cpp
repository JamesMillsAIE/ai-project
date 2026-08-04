#include "AI/Navigation/NavMesh.h"

#include "AI/Navigation/AStarPathfinder.h"
#include "AI/Navigation/NavMeshObstacles.h"

using p2t::Triangle;

NavMesh::NavMeshNode::NavMeshNode(const float cost, const vec3 location)
	: Node{ cost, location }, verticies{  }
{
	
}

int NavMesh::NavMeshNode::GetAdjacentVertices(NavMeshNode* other, vec3* adjacent)
{
	int count = 0;
	for (vec3 vert : verticies)
	{
		for (vec3 vert2 : other->verticies)
		{
			if (vert == vert2)
			{
				adjacent[count++] = vert;
				break;
			}
		}
	}

	return count;
}

NavMesh::NavMesh()
	: m_ctd{ nullptr }, m_pathfinder{ nullptr }
{}

NavMesh::~NavMesh()
{
	delete m_ctd;
}

void NavMesh::Build()
{
	// If the mesh has been built before, cleanup the old data
	if (m_ctd != nullptr)
	{
		delete m_pathfinder;
		delete m_ctd;

		for (const Poly2Point* point : m_meshPolyPoints)
		{
			delete point;
		}
		m_meshPolyPoints.clear();
	}

	// Create the CDT instance
	m_meshPolyPoints = PolyPoints();
	m_ctd = new CDT{ m_meshPolyPoints };

	// Add the obstacle holes
	for (NavMeshObstacle* obstacle : m_obstacles)
	{
		m_ctd->AddHole(obstacle->GetPoints());
	}

	// Run the triangulation algorithm
	m_ctd->Triangulate();

	TList<IPathfinder::Node*> nodes;
	for (Triangle* triangle : m_ctd->GetTriangles())
	{
		// Get the three points on the triangle
		const Poly2Point* point0 = triangle->GetPoint(0);
		const Poly2Point* point1 = triangle->GetPoint(1);
		const Poly2Point* point2 = triangle->GetPoint(2);

		// Generate the node
		NavMeshNode* node = new NavMeshNode
		{
			.verticies =
			{
				{ static_cast<float>(point0->x), static_cast<float>(point0->y), 0.f },
				{ static_cast<float>(point1->x), static_cast<float>(point1->y), 0.f },
				{ static_cast<float>(point2->x), static_cast<float>(point2->y), 0.f },
			}
		};

		// Generate the location and add it to the collection
		node->location = (node->verticies[0] + node->verticies[1] + node->verticies[2]) / 3.f;
		nodes.Add(node);
	}

	for (IPathfinder::Node* node : nodes)
	{
		for (IPathfinder::Node* node2 : nodes)
		{
			// Ignore the node if it is the same
			if (node == node2)
			{
				continue;
			}

			// Check if the nodes are sharing vertices
			vec3 n[2];
			if (dynamic_cast<NavMeshNode*>(node)->GetAdjacentVertices(dynamic_cast<NavMeshNode*>(node2), n) == 2)
			{
				// Connect the nodes
				const float mag = glm::length(node->location - node2->location);

				node->Connect(node2, mag);
				node2->Connect(node, mag);
			}
		}
	}

	m_pathfinder = new AStarPathfinder{ DefaultHeuristic, nodes };
}

vector<Poly2Point*> NavMesh::PolyPoints() const
{
	vector<Poly2Point*> points;
	points.reserve(m_meshPoints.Count());

	for (const vec3& point : m_meshPoints)
	{
		points.emplace_back(new Poly2Point{ point.x, point.y });
	}

	return points;
}
