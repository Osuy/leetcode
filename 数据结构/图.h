#pragma once
#include <vector>
#include <list>
#include <span>
using std::vector;
using std::list;
using std::span;

/*
	邻接矩阵

	邻接表

	V个点 E条边
	bfs遍历的时间复杂度是O(V+E)
	图是特殊的 多叉树。多叉树的遍历，边的数量 = 节点数量 - 1（每个节点都有连向父节点的边，根节点没有）
	所以时间复杂度是O(N + N - 1) = O(N)
	然而图不同，图的任意两个点都可以连线，最少N-1条边，最多N(N-1)条边。复杂的分别为O(N)和O(N^2)
	为了统一，使用边的数量来表示，都是 O(V+E)

*/

struct Vertex
{
	int id;
	vector<Vertex*> neighbors;
};

struct Edge
{
	int to;
	int weight;
};

class graph_t
{
	std::vector<std::vector<int>> matrix; // 邻接矩阵
	std::vector<std::vector<Edge>> list; // 邻接表

public:
	// dfs
	static void traverse(Vertex* s, span<bool> visited) 
	{	
		if (!s) 
		{
			return;
		}
		
		// 比起树的遍历 ，图的遍历要标记是否访问过，否则会造成死循环
		if (visited[s->id]) 
		{	
			return;
		}

		// 前序位置
		visited[s->id] = true;
		for (auto neighbor : s->neighbors) 
		{
			traverse(neighbor, visited);
		}
		// 后序位置
	}

	void traverse()
	{
		// 访问标记
		std::vector<bool> visited(matrix.size(), false);

		traverse(0, visited);
	}

	void traverse(int v, std::vector<bool>& visited)
	{
		if (v < 0 || v >= matrix.size())
		{
			return;
		}

		if (visited[v])
		{
			return;
		}

		// 前序位置
		visited[v] = true;
		for (auto neighbor : matrix[v])
		{
			if (neighbor)
			{
				traverse(neighbor, visited);
			}
		}
		// 遍历不需要撤销visited，因为要确保每个节点只访问一次
		// 但是如果是寻找路径，那么多条路径可以经过一个节点，所以需要撤销visited
	}
};