#include "AI/Navigation/NavMesh.h"

#include "AI/Navigation/AStarPathfinder.h"
#include "AI/Navigation/NavMeshObstacles.h"

constexpr int32 MAX_SMOOTHED_PATH_NODES = 128;

using p2t::Triangle;

namespace
{
	float TriArea(const vec3 a, const vec3 b, const vec3 c)
	{
		const float ax = b[0] - a[0];
		const float ay = b[1] - a[1];
		const float bx = c[0] - a[0];
		const float by = c[1] - a[1];
		return bx * ay - ax * by;
	}
}

int32 NavMesh::StringPull(const vec3* portals, const int32 nPortals, vec3* points, const int32 maxPoints)
{
	int nPoints = 0;

	// Setup the initial state
	vec3 portalApex = portals[0], portalLeft = portals[0], portalRight = portals[1];
	int apexIndex = 0, leftIndex = 0, rightIndex = 0;

	// Add the start point
	points[nPoints++] = portalApex;

	for (int i = 1; i < nPortals && nPortals < maxPoints; ++i)
	{
		vec3 left = portals[i * 2 + 0];
		vec3 right = portals[i * 2 + 1];

		// Update right vertex
		if (TriArea(portalApex, portalRight, right) <= 0.f)
		{
			if (portalApex == portalRight || TriArea(portalApex, portalLeft, right) > 0.f)
			{
				// Tighten the funnel
				portalRight = right;
				rightIndex = i;
			}
			else
			{
				points[nPoints++] = portalLeft;

				portalApex = portalLeft;
				apexIndex = leftIndex;

				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;

				// Restart scan
				i = apexIndex;
				continue;
			}
		}

		// Update left vertex
		if (TriArea(portalApex, portalLeft, left) >= 0.f)
		{
			if (portalApex == portalLeft || TriArea(portalApex, portalRight, left) < 0.f)
			{
				// Tighten the funnel
				portalLeft = left;
				leftIndex = i;
			}
			else
			{
				points[nPoints++] = portalRight;

				// Make current right the new apex
				portalApex = portalRight;
				apexIndex = rightIndex;

				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;

				// Restart scan
				i = apexIndex;
				continue;
			}
		}
	}

	if (nPoints < maxPoints)
	{
		points[nPoints] = portals[nPortals - 1];
	}

	return nPoints;
}

NavMesh::NavMeshNode::NavMeshNode()
	: Node{ 0.f, {} }, vertices{  }
{
	
}

int32 NavMesh::NavMeshNode::GetAdjacentVertices(NavMeshNode* other, vec3* adjacent)
{
	int count = 0;
	for (vec3 vert : vertices)
	{
		for (vec3 vert2 : other->vertices)
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
		NavMeshNode* node = new NavMeshNode;
		node->vertices[0] = { static_cast<float>(point0->x), static_cast<float>(point0->y), 0.f };
		node->vertices[1] = { static_cast<float>(point1->x), static_cast<float>(point1->y), 0.f };
		node->vertices[2] = { static_cast<float>(point2->x), static_cast<float>(point2->y), 0.f };

		// Generate the location and add it to the collection
		node->location = (node->vertices[0] + node->vertices[1] + node->vertices[2]) / 3.f;
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

TList<vec3> NavMesh::Calculate(const vec3 start, const vec3 end)
{
	// If the nav mesh hasn't been built before, build it
	if (m_pathfinder == nullptr)
	{
		Build();
	}

	// Use A* to calculate the the unsmoothed path
	TList<IPathfinder::Node*> path = m_pathfinder->Calculate(start, end);

	// Add the setup the portals with the start of the path
	int index = 0;
	vec3* portals = new vec3[(path.Count() + 1) * 2];
	portals[index++] = path.Front()->location;
	portals[index++] = path.Front()->location;

	NavMeshNode* prev = nullptr;
	for (IPathfinder::Node* n : path)
	{
		// If we have a previous node...
		NavMeshNode* node = dynamic_cast<NavMeshNode*>(n);
		if (prev != nullptr)
		{
			// Get the adjacent vertices and get the directions between them
			vec3 adj[2];
			prev->GetAdjacentVertices(node, adj);

			const vec3 fromPrev = node->location - prev->location;
			const vec3 toAdj0 = adj[0] - prev->location;

			if (fromPrev.x * toAdj0.x - toAdj0.y * fromPrev.y - toAdj0.z * fromPrev.z <= 0)
			{
				portals[index++] = adj[0];
				portals[index++] = adj[1];
			}
			else
			{
				portals[index++] = adj[1];
				portals[index++] = adj[0];
			}
		}

		prev = node;
	}

	// Add the last node to the portals
	portals[index++] = path.Back()->location;
	portals[index++] = path.Back()->location;

	// String pull the portals to get the smoothed path
	vec3 out[MAX_SMOOTHED_PATH_NODES];
	const int32 count = StringPull(portals, index / 2, out, MAX_SMOOTHED_PATH_NODES);

	// Convert the calculated string pull to the path list
	TList<vec3> smoothPath;
	smoothPath.Resize(count);

	for (int32 i = 0; i < count; ++i)
	{
		smoothPath[i] = out[i];
	}

	return smoothPath;
}