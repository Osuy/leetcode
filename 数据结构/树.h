#pragma once
#include <queue>
#include <vector>
#include <type_traits>
/*
	深度：

	二叉树的三种递归遍历dfs：前序、中序、后序
		其中二次搜索树中序遍历每个元素是递增的，即输出单调递增数组

	二叉树的层序遍历bfs三种形式：不带层数的、带层数的、每个节点都带权重和的


	二叉树的变体
		搜索树
		平衡搜索树（红黑树）
		trie树/字典树：如果要存储的大量字符串里存在统一的前缀，只保存一份前缀节省空间。遍历时可以获得所有自起点始的子串
			同时支持通配符，可以用正则表达式匹配字符串。适合用来做搜索引擎、代码补全等
			



*/

template<typename T>
class tree_t
{
	struct node_t
	{
		node_t* left = nullptr;
		node_t* right = nullptr;
		T val;
	};

	node_t* _root = nullptr;
public:

	// 最简单的层序遍历，不提供深度信息
	void bfs1(node_t* root)const
	{
		if (!root)return;

		std::queue<node_t*> queue{};
		queue.push(root);

		while (!queue.empty())
		{
			auto node = queue.front();
			queue.pop();

			// code to execute
			if (node.left) queue.push(node.left);
			if (node.right) queue.push(node.right);
		}
	}

	// 用额外变量记录了深度信息
	// 提前获取队列内元素的数量n，然后出队n次，相当于出队了一层
	// 每次出队就入队其子节点。所以循环内获取 queue.size() 是不可靠的
	// 出队完一层后，depth自增
	void bfs2(node_t* root)const
	{
		if (!root)return;

		std::queue<node_t*> queue{};
		queue.push(root);
		int depth = 1;

		while (!queue.empty())
		{
			
			int num = queue.size();
			for (int i = 0; i < num; ++i)
			{
				auto node = queue.front();
				queue.pop();

				// code to execute
				if (node.left) queue.push(node.left);
				if (node.right) queue.push(node.right);
			}

			++depth;
		}
	}

	// 方法2相当于所有权重都是1，如果遇到带权重的深度的问题，必须单独维护所有节点的带权深度
	void bfs3(node_t* root)const
	{
		if (!root)return;

		struct weighted_node_t
		{
			node_t* node = nullptr;
			int depth = 1;
		};

		std::queue<weighted_node_t> queue{};
		queue.push({ root, 1/*depth*/ });
		while (!queue.empty())
		{
			// 提前获取队列内元素的数量n，然后出队n次，相当于出队了一层
			// 每次出队就入队其子节点。所以循环内获取 queue.size() 是不可靠的
			int num = queue.size();
			for (int i = 0; i < num; ++i)
			{
				auto node = queue.front();
				queue.pop();

				// code to execute
				if (node.node.left) queue.push({ node.left, node.depth + 1/*1或权重*/});
				if (node.node.right) queue.push({ node.right, node.depth + 1/*1或权重*/ });
			}
		}
	}

	/*
	226.翻转二叉树
	将二叉树的左右子树互换

	对于每个节点，互换左右子节点，然后递归地去翻转子节点

	互换操作在前中后序三个位置都可以，但是注意，如果中序翻转，则递归原本要递归的右子树跑到左边了
	所以不在递归右子树，而是再递归一次左子树
	*/

	node_t* invertTree(node_t* node) const
	{
		if (node)
		{
			swap(node->left, node->right);

			invertTree(node->left);

			// swap(node->left, node->right);
			// invertTree(node->left);

			invertTree(node->right);

			//swap(node->left, node->right);

		}

		return root;
	}
};


/*
	二叉堆/优先队列
	底层不是二叉树而是数组。使用 index *2 index * 2 + 1得到左右子节点。因此index从1开始比较方便。
	上浮：如果父节点比自己大，则互换，重复操作直到没有父节点
	下沉：如果两个子节点中较小的一个比自己小，则互换，然后对该子节点重复操作，直到没有子节点
		因为是与较小的子节点互换，所以互换后，三者满足小顶堆，但子树可能不满足，所以要递归

	push：放到数组末尾，然后上浮
	pop：把末尾元素放到根节点，然后下沉

	构建小顶堆：从1开始遍历，对所有元素上浮操作。也可以理解为是多次push
		或者从末尾开始，对所有元素进行下沉。

*/
class priority_queue
{
	std::vector<int> arr;

	void _sink(int i)
	{
		int min = i;
		if (i * 2 + 1 < arr.size())
		{
			min = arr[i * 2] < arr[i * 2 + 1] ? i * 2 : i * 2 + 1;
			min = arr[min] < arr[i] ? min : i;

		}
		else if (i * 2 < arr.size() && arr[i * 2] < arr[i])
		{
			min = i * 2;
		}

		if (min == i)return;

		std::swap(arr[i], arr[min]);
		_sink(min);
	}

	void _sink_no_resercurive(int i)
	{
		int size = arr.size();
		int node = i;
		while (node * 2 < size || node * 2 + 1 < size)
		{
			int min = node;
			if (node * 2 + 1 < size)
			{
				min = arr[node * 2] < arr[i * 2 + 1] ? node * 2 : node * 2 + 1;
			}
			else if (node * 2 < size && arr[node * 2] < arr[i])
			{
				min = node * 2;
			}

			if (min == node)break;

			std::swap(arr[node], arr[min]);
			node = min;
		}
	}

	void _swim(int i)
	{

	}
};
