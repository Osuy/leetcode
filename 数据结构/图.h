#pragma once
#include <vector>
#include <list>
#include <span>
#include <queue>
using std::vector;
using std::list;
using std::span;

/*
	�ڽӾ���

	�ڽӱ�

	V���� E����
	bfs������ʱ�临�Ӷ���O(V+E)
	ͼ������� �������������ı������ߵ����� = �ڵ����� - 1��ÿ���ڵ㶼�����򸸽ڵ�ıߣ����ڵ�û�У�
	����ʱ�临�Ӷ���O(N + N - 1) = O(N)
	Ȼ��ͼ��ͬ��ͼ�����������㶼�������ߣ�����N-1���ߣ����N(N-1)���ߡ����ӵķֱ�ΪO(N)��O(N^2)
	Ϊ��ͳһ��ʹ�ñߵ���������ʾ������ O(V+E)

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
	std::vector<std::vector<int>> matrix; // �ڽӾ���
	std::vector<std::vector<Edge>> list; // �ڽӱ�

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
		
		// �������ı��� ��ͼ�ı���Ҫ����Ƿ���ʹ�������������ѭ��
		if (visited[s->id]) 
		{	
			return;
		}

		// ǰ��λ��
		visited[s->id] = true;
		for (auto neighbor : s->neighbors) 
		{
			traverse(neighbor, visited);
		}
		// ����λ��
	}

	void traverse()
	{
		// ���ʱ��
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

		// ǰ��λ��
		visited[v] = true;
		for (auto neighbor : matrix[v])
		{
			if (neighbor)
			{
				traverse(neighbor, visited);
			}
		}
		// ��������Ҫ����visited����ΪҪȷ��ÿ���ڵ�ֻ����һ��
		// ���������Ѱ��·������ô����·�����Ծ���һ���ڵ㣬������Ҫ����visited
	}
};

/*
	�ҿ�˹������Dijkstra���㷨����̬�滮˼�룩
	���ڴ�Ȩͼ����һ�����㵽�������ж�������·��
	��ԭ���prim�㷨���ƣ����Ǹ��±߼��Ĺ�����Щ��ͬ

	����˼�룺
		�������Ȩͼ�Ķ����Ϊ�������ϣ�1.���v�������v�������·���Ķ���ļ���S��2.ʣ�ඥ��U

		1.��ʼʱ��S������v��v��U����һ����i�����·��Ϊe(v, i)��Ȩֵ��û�б���·������ΪINF��
		2.ѡȡ����S����ĵ�u������S
		3.����v��U��������·������v�ȵ�u�ٵ�i��·����Ȩֵ�͸�С�����޸�v��i���·����ֵ
		4.�ظ�2��3��ֱ��ѭ�� n-1�Σ������ж��������S

	ÿ������ֻ�����Sһ�Σ����Բ�����ڻ�

	��Զ�������붥�㣬�����ĵ�һ����ǰ����ĵ����v��Զ

	һ����ԣ����һ��·����Ҫһ�����飬���·���ϵ����бߡ���ô����������·����Ҫһ����ά����
	���ǵҿ�˹�����㷨������е����·��ֻ����һ��һά���顣
	��ԭ���ǡ����v, ..., i, j��v��j�����·��������iΪj��ǰһ���㡣��ôiһ����j������뵽S��
	����i�����·���Լ�ȷ������ôjֻ��Ҫ��ס����ǰһ���㣬����׷�ݳ��Լ���v�����·��
	��ôֻ��Ҫ�������ﱣ��i���ɡ���path[j] = i;

	ʱ�临�Ӷ�O(N), �ռ临�Ӷ�O(N)��Dijkstra�Ŀռ临�Ӷȶ���O(N)�������ص�˵����


	��֧�ָ�Ȩ�أ���Ϊ��������ǰ���ǣ�����Զ·��Ȩ�ػ�Խ��Խ�󡱣�
	����и�Ȩ�أ���ǰ�᲻����
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
		dist[i] = g.edges()[v][i]; // ֱ�ӽ�v�����е�ı���Ϊ���·��
		S[i] = false;
		if (g.edges()[v][i] < INT_MAX) // ������ڱߣ���ǰ���ڵ��ʼ��Ϊv������Ϊ-1
			Path[i] = v;
		else
			Path[i] = -1;
	}

	//��v����S����v��v��ǰ��Ϊ-1��
	S[v] = 1;
	Path[v] = -1;

	for (i = 1; i < n; ++i)// ÿ��ѭ���ͼ���һ����S����ѭ������ n-1
	{
		min = INT_MAX;
		for (j = 0; j < n; ++j) // Ѱ��S����ʣ������СȨֵ��
		{
			if (!S[j] && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}

		// ��k����S��
		S[k] = 1;

		//��Ϊk����S�������������·�������v�ȵ�k�ٵ�j��·��С��vֱ�ӵ�j����ô����dist[j]
		//����k��Ϊv��j��ǰ���ڵ�
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
	���ȶ����Ż���İ汾
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
		dist[i] = g.edges()[v][i]; // ֱ�ӽ�v�����е�ı���Ϊ���·��
		
		if (g.edges()[v][i] < INT_MAX) // ������ڱߣ���ǰ���ڵ��ʼ��Ϊv������Ϊ-1
			Path[i] = v;
		else
			Path[i] = -1;
	}

	Path[v] = -1;

	while(!q.empty())
	{
		auto e = q.top();
		q.pop();

		if (dist[e.id] < e.dist)// �����ɱ�
		{
			continue;
		}
		// �˴���������һ�������������ﵽn-1ʱbreak
		dist[e.id] = e.dist;
		
		for (int i = 0; i < n; ++i)
		{
			if (e.dist + g.edges()[e.id][i] < dist[i]) // ����e.id��i������������±�
			{
				q.emplace(i, e.dist + g.edges()[e.id][i]);
			}
		}
	}

	return { Path, dist };
}