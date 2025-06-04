#pragma once
#include"../base_header.h"

namespace q297
{

struct TreeNode 
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
string serialize(TreeNode* root) {
	stringstream ss;
	auto dfs = [&ss](this auto&& dfs, TreeNode* node)->void
		{
			if (!node)
			{
				ss << "#,";
				return;
			}

			ss << node->val << ',';
			dfs(node->left);
			dfs(node->right);
		};
	dfs(root);
	return ss.str();
}

TreeNode* deserialize(string data)
{
	stringstream ss{ data };
	auto dfs = [&ss](this auto&& dfs)->TreeNode*
		{
			string item;
			getline(ss, item, ',');
			if ("#" == item || item.empty())return nullptr;

			// 序列化是前序遍历，反序列化也是前序遍历
			auto node = new TreeNode{ atoi(item.data()) };
			node->left = dfs();
			node->right = dfs();

			return node;
		};

	return dfs();
}

}