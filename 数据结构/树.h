#pragma once
#include <queue>
#include <vector>
#include <type_traits>
/*
	��ȣ�

	�����������ֵݹ����dfs��ǰ�����򡢺���
		���ж����������������ÿ��Ԫ���ǵ����ģ������������������

	�������Ĳ������bfs������ʽ�����������ġ��������ġ�ÿ���ڵ㶼��Ȩ�غ͵�


	�������ı���
		������
		ƽ�����������������
		trie��/�ֵ��������Ҫ�洢�Ĵ����ַ��������ͳһ��ǰ׺��ֻ����һ��ǰ׺��ʡ�ռ䡣����ʱ���Ի�����������ʼ���Ӵ�
			ͬʱ֧��ͨ�����������������ʽƥ���ַ������ʺ��������������桢���벹ȫ��
			



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

	// ��򵥵Ĳ�����������ṩ�����Ϣ
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

	// �ö��������¼�������Ϣ
	// ��ǰ��ȡ������Ԫ�ص�����n��Ȼ�����n�Σ��൱�ڳ�����һ��
	// ÿ�γ��Ӿ�������ӽڵ㡣����ѭ���ڻ�ȡ queue.size() �ǲ��ɿ���
	// ������һ���depth����
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

	// ����2�൱������Ȩ�ض���1�����������Ȩ�ص���ȵ����⣬���뵥��ά�����нڵ�Ĵ�Ȩ���
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
			// ��ǰ��ȡ������Ԫ�ص�����n��Ȼ�����n�Σ��൱�ڳ�����һ��
			// ÿ�γ��Ӿ�������ӽڵ㡣����ѭ���ڻ�ȡ queue.size() �ǲ��ɿ���
			int num = queue.size();
			for (int i = 0; i < num; ++i)
			{
				auto node = queue.front();
				queue.pop();

				// code to execute
				if (node.node.left) queue.push({ node.left, node.depth + 1/*1��Ȩ��*/});
				if (node.node.right) queue.push({ node.right, node.depth + 1/*1��Ȩ��*/ });
			}
		}
	}

	/*
	226.��ת������
	����������������������

	����ÿ���ڵ㣬���������ӽڵ㣬Ȼ��ݹ��ȥ��ת�ӽڵ�

	����������ǰ�к�������λ�ö����ԣ�����ע�⣬�������ת����ݹ�ԭ��Ҫ�ݹ���������ܵ������
	���Բ��ڵݹ��������������ٵݹ�һ��������
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
	�����/���ȶ���
	�ײ㲻�Ƕ������������顣ʹ�� index *2 index * 2 + 1�õ������ӽڵ㡣���index��1��ʼ�ȽϷ��㡣
	�ϸ���������ڵ���Լ����򻥻����ظ�����ֱ��û�и��ڵ�
	�³�����������ӽڵ��н�С��һ�����Լ�С���򻥻���Ȼ��Ը��ӽڵ��ظ�������ֱ��û���ӽڵ�
		��Ϊ�����С���ӽڵ㻥�������Ի�������������С���ѣ����������ܲ����㣬����Ҫ�ݹ�

	push���ŵ�����ĩβ��Ȼ���ϸ�
	pop����ĩβԪ�طŵ����ڵ㣬Ȼ���³�

	����С���ѣ���1��ʼ������������Ԫ���ϸ�������Ҳ�������Ϊ�Ƕ��push
		���ߴ�ĩβ��ʼ��������Ԫ�ؽ����³���

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
