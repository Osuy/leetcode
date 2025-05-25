#pragma once
#include "TreeNode.h"
/*
	难度：困难
	求二叉树中的二叉搜索树的元素和的最大值
	此题的解法需要建立在98.验证二叉搜索树上
	在遍历子树的同时，用第三个变量去记录树的元素和

	由于不要求整体是二叉搜索树，而是去寻找可能存在的二叉搜索树
	所以如果左子树不是二叉搜素树，依然要去递归右子树
*/
namespace q1373
{
int maxSumBST(TreeNode* root) 
{
	int ans = 0;

	auto recursion = [&ans](this auto&& recursion, TreeNode* node, int& min, int& max, int& sum) ->bool
		{
			if (!node)return true;
			int lmax = node->val, rmin = node->val;
			min = max = node->val;
			int lsum = 0, rsum = 0;
			// 两个子树都要递归，即便左子树不是二叉搜索树
			auto rl = recursion(node->left, min, lmax, lsum);
			auto rr = recursion(node->right, rmin, max, rsum);

			const bool is_bst = rl && rr
				&& (!node->left || lmax < node->val)
				&& (!node->right || rmin > node->val);

			if (is_bst)
			{
				sum = node->val + lsum + rsum;
				ans = std::max(ans, sum);
			}
			return is_bst;
		};

	int min, max, sum;
	recursion(root, min, max, sum);

	return ans;
}
}