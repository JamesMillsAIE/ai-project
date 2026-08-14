#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <raylib/raylib.h>

using std::function;
using std::vector;

namespace AiForGames
{
	struct Node;

	struct Edge
	{
		float cost = 1.f;
		Node* endPoint = nullptr;
	};

	struct Node
	{
	public:
		Vector2 location;
		float gScore = 0.f;

		float cost = 1.f;
		vector<Edge> edges = {};

	public:
		explicit Node(Vector2 location);

	public:
		void Connect(Node* endPoint, float c = 1.f);

	};

	class NodeGraph
	{
	private:
		Node*** m_graph;

		int32_t m_width;
		int32_t m_height;
		float m_nodeSpacing;

		Texture2D m_nodeMapTex;

	public:
		NodeGraph(const Image& nodeMap, float nodeSpacing);
		~NodeGraph();

	public:
		void Render() const;
		Node*** Get() const;

	private:
		void IterateGraph(const function<void(Node*, int32_t, int32_t)>& iterator, int32_t offsetXMax = 0, int32_t offsetYMax = 0) const;

	};
}