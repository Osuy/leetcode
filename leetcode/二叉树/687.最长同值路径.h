#pragma once
#include "../base_header.h"
#include "TreeNode.h"
/*
	难度：中等
	求二叉树中由相同值组成的路径的最大长度
	路径可以不经过根节点

	由于路径可以不经过根节点，于是答案可能完全藏在子树里
	假若已经知道左子树和右子树里的同值最长路径
	现在需要求的应该是：左子树里的同值最长路径、右子树里的同值最长路径、经过自己的同值最长路径，三者的最大值
	而求经过自己的同值最长路径需要用到：以左右子节点为末尾的同值最长路径
	然后如果左右自节点的值与自己相同，则可以将三者相加得到经过自己的同值最长路径
	同时还需将自己树中的同值最长路径和以自己为末尾的同值最长路径返回到上一层递归里
*/

int longestUnivaluePath(TreeNode* root)
{
	auto recursion = [](this auto&& recursion, TreeNode* node)->pair<int, int> // 返回树内的同值最长路径和以自己为末尾的同值最长路径
		{
			if (!node)return { 0, 0 };

			auto left = recursion(node->left);
			auto right = recursion(node->right);

			int l1 = 1;
			int l2 = max(left.second, right.second);

			// 左节点与自己相等，则以自己为末尾的同值最长路径是左的加一
			if (node->left && node->left->val == node->val)
			{
				l1 = 1 + left.first;
			}

			// 右节点与自己相等，则以自己为末尾的同值最长路径是右的加一
			if (node->right && node->right->val == node->val)
			{
				l1 = max(l1, 1 + right.first);
			}

			// 左右节点与自己相同，则树内的同值最长路径是左加右加一
			if (node->left && node->left->val == node->val
				&& node->right && node->right->val == node->val)
			{
				l2 = max(l2, 1 + left.first + right.first);
			}

			return { l1, max(l1, l2) };
		};

	return max(0, recursion(root).second - 1);
}