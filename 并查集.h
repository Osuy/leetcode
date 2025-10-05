#pragma once
#include <vector>
#include <numeric>
/*
	ͼ�ı���
	���ӡ���ѯ�Ƿ����ӡ���ѯ�м�����ͨ������ʱ�临�Ӷȶ���O(n)

	ԭ��
	��һ����ͨ������Ϊһ�������
	�Ƿ����ӣ��ж������ڵ�ĸ��ڵ��Ƿ���ͬ��
	���ӣ���һ���ڵ�ĸ��ڵ����ӵ���һ���ڵ�ĸ��ڵ���
	��ͨ�������������ڵ������

	�������Ż�
	1.�����������ڵ�ʱ������ѽڵ��������p���ӵ��ڵ����ٵ���q�£��ᵼ��q����������
	����Ӧ���ж��������Ľڵ������ѽ��ٵ����ӵ��϶������

	2.����ʹ����1���Ż����ڶ�β����󣬲��鼯��������Ȼ���˻�Ϊlogn����Ҫ���ֳ���ʱ�临�Ӷ�
	һ�����µ����нڵ�Ӧ�ö�ֱ�����Ӹ��ڵ㣬���߶�Ϊ2
	Ҳ����Ҫ�ͳ���һ���߶ȵ�������ȡѹ��
*/

class UnionFind
{
public:
	struct node
	{
		int id = 0;
		node* parent = nullptr;
	};
private:
	int _count = 0;
	std::vector<int> _parents;

	// �Ż�
	std::vector<int> _size;


	node* root_of(node* p)const
	{
		if (!p)return nullptr;

		// p�и��ڵ㣬�����ѹ��
		if (p->parent)
		{
			p->parent = root_of(p->parent);
			return p->parent;
		}

		// p�޸��ڵ㣬�Լ����Ǹ�
		return p;
	}

	int root_of(int x)const
	{
		while (x != _parents[x])
		{
			// x = _parents[x]; // �������ϲ��Ҹ��ڵ㣬�����޸��������Ż�
			/*
				ѹ���Ż�
				ѹ�������֣�һ������Сѹ����һ������ȫѹ��
				��Сѹ���ǽ�������Сһ�룬����ȫѹ���ǰ�����ѹ��Ϊ2��Ҳ�������нڵ㶼ֱ��ָ����ڵ�
				��Сѹ���Ĺ����ǵ�x�ĸ��ڵ㲻Ϊ��ʱ�����游�ڵ㣩����x�ĸ��ڵ�ָ���游�ڵ�
				Ȼ��x = x�ĸ��ڵ㣬ѭ��ֱ�����ڵ�
				��Ȼ����x�ĸ��ڵ������ѭ������ô��ѭ����ͬʱҲ����ѹ��
				��������ѹ����ѭ��ֱ�����ڵ㣬��ôѹ���㷨��������������Ҹ��ڵ�
			*/
			const_cast<UnionFind*>(this)->_parents[x] = _parents[_parents[x]];
			x = _parents[x];
		}

		return x;
		/*
			��ȫѹ�����Ϊ���ף�����ѹ��x�ڵ��ͬʱ���ݹ�ȥѹ��x�ĸ��ڵ�
			����x�����ڵ��ϵ����нڵ㣬����ѹ��
			��Сѹ��ֻ�ǰ�x�ĸ��ڵ��޸�Ϊ�游������ȫѹ���ķ���ֵ�Ǹ��ڵ�
			���ԶԵݹ��е�ÿ���ڵ�x'�ĸ��ڵ����Ǳ��޸�Ϊ���ڵ�
		*/
		if (x != _parents[x])
		{
			const_cast<UnionFind*>(this)->_parents[x] = root_of(_parents[x]);
		}

		return _parents[x];
	}


public:
	UnionFind(int n)
		: _count{ n }
		, _size(n, 1)
	{
		for (int i = 0; i < n; ++i)
		{
			_parents.push_back(i);// ÿ���ڵ�ĸ��ڵ�����Լ�
		}
	}

	void connect(int p, int q)
	{
		auto rp = root_of(p);
		auto rq = root_of(q);
		if (rp == rq)return;
		--_count;
		_parents[rp] = rq;
	}

	void connect(node* p, node* q)
	{
		// ��p�ĸ��ڵ����ӵ�q�ĸ��ڵ���
		root_of(p)->parent = root_of(q);
	}

	bool is_connected(node* p, node* q)const
	{
		return root_of(p) == root_of(q);
	}

	bool is_connected(int p, int q)const
	{
		return root_of(p) == root_of(q);
	}

	int count()const
	{
		return _count;
	}
};

class UnionFind2
{
	int _count = 0;
	std::vector<int> _parent;

public:
	UnionFind2(int n)
		: _count{ n }
		, _parent(n, 0)
	{
		std::iota(_parent.begin(), _parent.end(), 0);
	}

	int root_of(int p)const
	{
		if (p != _parent[p])
		{
			const_cast<UnionFind2*>(this)->_parent[p] = root_of(_parent[p]);
		}
	}

	void connect(int p, int q)
	{
		auto rp = root_of(p);
		auto rq = root_of(q);
		if (rp == rq)return;
		--_count;
		_parent[rq] = rp;
	}

	bool is_connected(int p, int q)const
	{
		return root_of(p) == root_of(q);
	}

	int count()const
	{
		return _count;
	}
};