#pragma once
#include "../base_header.h"
#include "TreeNode.h"
/*
	难度：中等
	给出一个二叉树和一个数组
	二叉树的节点数和数组长度都为n，且节点的值和数组元素都为1~n且互不相同
	将二叉树翻转部分节点，使其先序遍历与数组相同
	如果无法翻转得到结果，返回-1

	此题建立在226.翻转二叉树的基础上，但需要满足条件
	假设index指向当前node对应的数组位置
	如果nums[index] ！= node->val 则无法翻转成功，返回 -1
	如果 node->left && nums[index + 1] ！= node->left->val，则左节点与数组值不匹配，将其翻转
		至于翻转后右节点是否匹配，无需验证，留给递归

*/

vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage)
{
	int index = 0;
	vector<int> ans;
	auto recursion = [&](this auto&& recursion, TreeNode* node)->bool
		{
			if (!node)return true;
			if (voyage[index] != node->val)
			{
				return false;
			}
			++index;
			if (node->left && node->left->val != voyage[index])
			{
				swap(node->left, node->right);
				ans.push_back(node->val);
			}
			return recursion(node->left) && recursion(node->right);
		};

	return recursion(root) ? ans : vector<int>{ -1 };
}