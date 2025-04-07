#pragma once
#include <vector>
#include <list>
#include <span>
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