#pragma once
#include "TreeNode.h"
#include "../base_header.h"
/*
	难度：中等（困难）
	在n个节点的二叉树中，每个节点有node.val个硬币，所有节点的值的和为n
	每次将一个硬币挪给相邻的节点
	求二叉树每个节点都有一个硬币的挪动最小次数

	相当于求硬币经过节点数量之和，而二叉树遍历恰好遍历所有节点
	所以只需要知道：1每个节点是否要挪硬币；2.每个节点要挪多少个硬币
	即可求解
	分解问题，如果已知左右子树的挪动次数为l和r
	由于存在要挪给子树硬币和从子树那里挪出硬币两种可能，可以分别用正负数表示
	于是每个节点要挪多少个硬币就等于挪给子树硬币和从子树那里挪出的值的绝对值
	因此可以不考虑硬币个数，只把它当作一个整数，从父节点那里获取，并传递给左右子树
	最后变化的数值就是通过该节点的硬币的数量
*/

int distributeCoins(TreeNode* root)
{
	auto recursion = [](this auto&& recursion, TreeNode* node, int& coins)->int
		{
			if (!node)return 0;

			// 自己留下一个硬币，其余的传递给左右子树
			int c = coins + node->val - 1;
			auto left = recursion(node->left, c);
			auto right = recursion(node->right, c);

			auto ret = left + right + abs(coins - c); // 左子树挪动次数 + 右子树挪动次数 + 硬币的变化个数的绝对值
			coins = c;
			return ret;
		};

	int coins = 0;
	return recursion(root, coins);
}