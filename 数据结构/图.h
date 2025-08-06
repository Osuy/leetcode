#pragma once
#include <vector>
#include <list>
#include <span>
#include <queue>
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
	const std::vector<std::vector<int>>& edges()const { return matrix; }
	int node_num()const
	{
		return list.size();
	}

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

/*
	狄克斯特拉（Dijkstra）算法（动态规划思想）
	对于带权图，求一个顶点到其他所有顶点的最短路径
	其原理和prim算法相似，但是更新边集的规则有些许不同

	基本思想：
		将有向带权图的顶点分为两个集合，1.起点v和已求出v到其最短路径的顶点的集合S；2.剩余顶点U

		1.初始时，S仅包含v。v到U中任一顶点i的最短路径为e(v, i)的权值（没有边则路径长度为INF）
		2.选取距离S最近的点u，加入S
		3.更新v到U顶点的最短路径，若v先到u再到i的路径的权值和更小，则修改v到i最短路径的值
		4.重复2和3，直到循环 n-1次，即所有顶点加入了S

	每个顶点只会加入S一次，所以不会存在环

	由远到近加入顶点，后加入的点一定比前加入的点距离v更远

	一般而言，存放一条路径需要一个数组，存放路径上的所有边。那么存放所有最短路径需要一个二维数组
	但是狄克斯特拉算法存放所有的最短路径只用了一个一维数组。
	其原理是。如果v, ..., i, j是v到j的最短路径，其中i为j的前一个点。那么i一定比j更早加入到S中
	所以i的最短路径以及确定，那么j只需要记住它的前一个点，就能追溯出自己到v的最短路径
	那么只需要在数组里保存i即可。即path[j] = i;

	时间复杂度O(N), 空间复杂度O(N)（Dijkstra的空间复杂度都是O(N)，不再特地说明）


	不支持负权重，因为求最近点的前提是：“绕远路的权重会越加越大”，
	如果有负权重，则前提不成立
*/

std::pair<std::vector<int>, std::vector<int>> Dijkstra(const graph_t& g, int v)
{
	auto n = g.node_num();
	std::vector<int> Path(n);
	std::vector<int> dist(n, INT_MAX);
	std::vector<bool> S(n, false);
	int i, j, k;
	int min;
	for (i = 0; i < n; ++i)
	{
		dist[i] = g.edges()[v][i]; // 直接将v到所有点的边作为最短路径
		S[i] = false;
		if (g.edges()[v][i] < INT_MAX) // 如果存在边，则前驱节点初始化为v，否则为-1
			Path[i] = v;
		else
			Path[i] = -1;
	}

	//将v加入S集，v到v的前驱为-1；
	S[v] = 1;
	Path[v] = -1;

	for (i = 1; i < n; ++i)// 每次循环就加入一个到S集，循环次数 n-1
	{
		min = INT_MAX;
		for (j = 0; j < n; ++j) // 寻找S集到剩余点的最小权值边
		{
			if (!S[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}

		// 将k加入S集
		S[k] = 1;

		//因为k加入S，更新其他最短路径，如果v先到k再到j的路径小于v直接到j，那么更新dist[j]
		//并把k作为v到j的前驱节点
		for (j = 0; i < n; ++j)
		{
			if (!S[j])
			{
				if (g.edges()[k][j] < INT_MAX && dist[k] + g.edges()[k][j] < dist[j])
				{
					dist[j] = dist[k] + g.edges()[k][j];
					Path[j] = k;
				}
			}
		}
	}

	return { Path, dist };
}

/*
	优先队列优化后的版本
*/

std::pair<std::vector<int>, std::vector<int>> Dijkstra(const graph_t& g, int v)
{
	auto n = g.node_num();
	std::vector<int> Path(n);
	std::vector<int> dist(n, INT_MAX);
	struct edge
	{
		int id;
		int dist;

		bool operator<(const edge& other)const
		{
			return dist < other.dist;
		}
	};
	std::priority_queue<edge, std::vector<edge>, std::greater<edge>> q;

	for (int i = 0; i < n; ++i)
	{
		dist[i] = g.edges()[v][i]; // 直接将v到所有点的边作为最短路径
		
		if (g.edges()[v][i] < INT_MAX) // 如果存在边，则前驱节点初始化为v，否则为-1
			Path[i] = v;
		else
			Path[i] = -1;
	}

	Path[v] = -1;

	while(!q.empty())
	{
		auto e = q.top();
		q.pop();

		if (dist[e.id] < e.dist)// 跳过旧边
		{
			continue;
		}
		// 此处可以增加一个计数变量，达到n-1时break
		dist[e.id] = e.dist;
		
		for (int i = 0; i < n; ++i)
		{
			if (e.dist + g.edges()[e.id][i] < dist[i]) // 经过e.id到i更近，则加入新边
			{
				q.emplace(i, e.dist + g.edges()[e.id][i]);
			}
		}
	}

	return { Path, dist };
}