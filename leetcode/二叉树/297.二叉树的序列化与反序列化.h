#pragma once
#include "../base_header.h"
namespace q297
{

struct TreeNode 
{
	int val;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
	TreeNode(int x) : val(x) {}
};

TreeNode* deserialize(string data) 
{
	if (data.empty())return nullptr;

	auto i = data.find('@');
	auto tmp = data.substr(0, i);
	data = data.substr(i + 1);
	if (tmp == "#")return nullptr;
	auto node = new TreeNode{ atoi(tmp.data()) };
	stack<TreeNode*> nodes;
	nodes.push(node);
	auto root = node;
	node = nullptr;
	while (!data.empty())
	{
		// #
		// 1@2@#@#@3@4@#@#@5@#@#
		i = data.find('@');
		tmp = data.substr(0, i);
		data = i == string::npos ? "" : data.substr(i + 1);

		if (node)
		{
			if (tmp == "#")
			{
				if (!nodes.empty())
				{
					node = nodes.top();
					nodes.pop();
				}
			}
			else
			{
				node->right = new TreeNode{ atoi(tmp.data()) };
				nodes.push(node->right);
				node = nullptr;
			}
		}
		else
		{
			if (tmp == "#")
			{
				node = nodes.top();
				nodes.pop();
			}
			else
			{
				node = new TreeNode{ atoi(tmp.data()) };
				nodes.top()->left = node;
				nodes.push(node);
				node = nullptr;
			}
		}
	}

	return node;
}

void test()
{
	string text{ "1@2@#@#@3@4@#@#@5@#@#" };

	deserialize(text);
}
}