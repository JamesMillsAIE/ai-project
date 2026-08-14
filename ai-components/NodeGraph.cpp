#include "NodeGraph.h"

#include <raylib/raymath.h>

namespace
{
	bool CmpColor(const Color lhs, const Color rhs, const bool cmpAlpha = false)
	{
		return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && (lhs.a == rhs.a || !cmpAlpha);
	}
}

namespace AiForGames
{
	Node::Node(Vector2 location) :
		location{location} {}

	void Node::Connect(Node* endPoint, float c)
	{
		edges.emplace_back(c, endPoint);
	}

	NodeGraph::NodeGraph(const Image& nodeMap, const float nodeSpacing) :
		m_width{nodeMap.width}, m_height{nodeMap.height}, m_nodeSpacing{nodeSpacing},
		m_nodeMapTex{LoadTextureFromImage(nodeMap)}
	{
		m_graph = new Node* *[m_height];
		for (int32_t y = 0; y < m_height; ++y)
		{
			m_graph[y] = new Node*[m_width];
			for (int32_t x = 0; x < m_width; ++x)
			{
				const Color color = GetImageColor(nodeMap, x, y);
				const Vector2 nodeLoc =
				{
					.x = static_cast<float>(x) * nodeSpacing + nodeSpacing * .5f,
					.y = static_cast<float>(y) * nodeSpacing + nodeSpacing * .5f
				};

				m_graph[y][x] = CmpColor(color, {255, 0, 0, 255}) ? nullptr : new Node{nodeLoc};
			}
		}

		IterateGraph([this](Node* node, const int32_t x, const int32_t y)
		{
			if (Node* east = m_graph[y][x + 1])
			{
				node->Connect(east);
				east->Connect(node);
			}

			if (Node* south = m_graph[y + 1][x])
			{
				node->Connect(south);
				south->Connect(node);
			}

			if (Node* southEast = m_graph[y + 1][x + 1])
			{
				node->Connect(southEast);
				southEast->Connect(node);
			}

			if (x - 1 < 0)
			{
				return;
			}

			if (Node* southWest = m_graph[y + 1][x - 1])
			{
				node->Connect(southWest);
				southWest->Connect(node);
			}
		}, 1, 1);

		UnloadImage(nodeMap);
	}

	NodeGraph::~NodeGraph()
	{
		for (int32_t y = 0; y < m_height; ++y)
		{
			for (int32_t x = 0; x < m_width; ++x)
			{
				delete m_graph[y][x];
			}

			delete[] m_graph[y];
		}

		delete[] m_graph;
	}

	void NodeGraph::Render() const
	{
		DrawTextureEx(m_nodeMapTex, Vector2Zero(), 0.f, m_nodeSpacing, WHITE);

		if (!IsKeyDown(KEY_GRAVE))
		{
			return;
		}

		IterateGraph([this](const Node* node, int32_t x, int32_t y)
		{
			for (const auto [cost, endPoint] : node->edges)
			{
				DrawLineV(node->location, endPoint->location, GRAY);
			}
		});

		IterateGraph([this](const Node* node, int32_t x, int32_t y)
		{
			DrawCircleV(node->location, m_nodeSpacing * .25f, WHITE);
			DrawCircleLinesV(node->location, m_nodeSpacing * .25f, GRAY);
		});
	}

	Node*** NodeGraph::Get() const
	{
		return m_graph;
	}

	void NodeGraph::IterateGraph(const function<void(Node*, int32_t, int32_t)>& iterator,
	                             const int32_t offsetXMax, const int32_t offsetYMax) const
	{
		for (int32_t y = 0; y < m_height - offsetXMax; ++y)
		{
			for (int32_t x = 0; x < m_width - offsetYMax; ++x)
			{
				if (Node* node = m_graph[y][x])
				{
					iterator(node, x, y);
				}
			}
		}
	}
}
