#pragma once
#include <vector>
#include <numeric>
/*
	图的变体
	连接、查询是否连接、查询有几个连通分量的时间复杂度都是O(n)

	原理
	把一个连通分量视为一个多叉树
	是否连接：判断两个节点的根节点是否相同，
	连接：将一个节点的根节点连接到另一个节点的根节点下
	连通分量数量：根节点的数量

	问题与优化
	1.在连接两个节点时，如果把节点数多的树p连接到节点数少的树q下，会导致q的树高增加
	所以应该判断两个树的节点数，把较少的连接到较多的下面

	2.即便使用了1的优化，在多次操作后，并查集的性能依然会退化为logn，而要保持常数时间复杂度
	一个树下的所有节点应该都直接连接根节点，即高度为2
	也就是要就超过一定高度的树，采取压缩
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

	// 优化
	std::vector<int> _size;


	node* root_of(node* p)const
	{
		if (!p)return nullptr;

		// p有父节点，则进行压缩
		if (p->parent)
		{
			p->parent = root_of(p->parent);
			return p->parent;
		}

		// p无父节点，自己就是根
		return p;
	}

	int root_of(int x)const
	{
		while (x != _parents[x])
		{
			// x = _parents[x]; // 单纯向上查找根节点，不会修改树，无优化
			/*
				压缩优化
				压缩有两种，一种是缩小压缩，一种是完全压缩
				缩小压缩是将树高缩小一半，而完全压缩是把树高压缩为2，也就是所有节点都直接指向根节点
				缩小压缩的过程是当x的父节点不为根时（有祖父节点），把x的父节点指向祖父节点
				然后x = x的父节点，循环直到根节点
				既然查找x的根节点会向上循环，那么在循环的同时也进行压缩
				反过来，压缩会循环直至根节点，那么压缩算法本身就能用来查找根节点
			*/
			const_cast<UnionFind*>(this)->_parents[x] = _parents[_parents[x]];
			x = _parents[x];
		}

		return x;
		/*
			完全压缩则更为彻底，它在压缩x节点的同时，递归去压缩x的父节点
			于是x到根节点上的所有节点，都被压缩
			缩小压缩只是把x的父节点修改为祖父，而完全压缩的返回值是根节点
			所以对递归中的每个节点x'的父节点总是被修改为根节点
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
			_parents.push_back(i);// 每个节点的父节点就是自己
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
		// 将p的根节点连接到q的根节点上
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