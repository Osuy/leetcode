#pragma once
#include "../base_header.h"

namespace q95
{
/*
	难度：中等
	给定数字n，构造出所有由1~n构成的二叉搜索树

	每个值都可以作为根节点，然后比它小的必然用于构造左子树
	比它大的必然由于构造右子树，递归即可
	对于相同的根节点，两个子树不同则为不同的二叉搜索树，所以需后序遍历结构
	自底向上构造出所有可能的子树，在构造出所有可能的树
*/

struct TreeNode
{
	int val = 0;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

vector<TreeNode*> build(int lo, int hi)
{
	// 基于区间去计算
	vector<TreeNode*> ans;
	// 如果区间为空，则插入一个空节点，使父节点至少有1中可能的子树，即空子树
	if (lo > hi)
	{
		ans.push_back(nullptr);
		return ans;
	}

	// lo与hi之间的每个值都可以作为根节点，确定根节点的值i
	// 先递归去构造左子树[lo, i-1] 和右子树 [i+1, hi] 的所有可能
	// 那么以i为根的二叉搜索树的所有可能，就是左子树的可能 * 右子树的可能
	for (int i = lo; i <= hi; ++i)
	{
		auto leftTree = build(lo, i - 1);
		auto rightTree = build(i + 1, hi);

		for (auto& left : leftTree)
		{
			for (auto& right : rightTree)
			{
				auto node = new TreeNode{ i, left, right };
				ans.push_back(node);
			}
		}
	}

	return ans;
}

vector<TreeNode*> generateTrees(int n) {
	return build(1, n);
}
}