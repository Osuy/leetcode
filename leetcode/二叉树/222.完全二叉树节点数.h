#pragma once
#include "TreeNode.h"
#include "../base_header.h"

/*
	难度：中等
	求完全二叉树的节点数。完全二叉树是只有最底层的右边存在空节点的二叉树

	首先求二叉树的节点数，完整遍历一边即可，复杂度O(N)
	但是没有运用完全二叉树的性质
	完全二叉树的最底层右边存在空节点，
		1.要么空节点的数量小于等于一半，于是根节点的左子树一定是满二叉树，右子树依然是完全二叉树
		2.妖媚空节点的数量大于一半，于是根节点的左子树是完全二叉树，右子树是高度-1的满二叉树


	可见问题可以被转化为求：一个满二叉树和一个完全二叉树的节点数之和
	那样就形成了递归
	求满二叉树的节点数，即：2^h - 1
	求完全二叉树的节点数：不断地递归，把当中的完全二叉树不断分解为一个满二叉树和一个完全二叉树
*/

int countNodes(TreeNode* root) 
{
	if (!root)return 0;

	auto hl = 1, hr = 1; // 高度从1开始
	auto l = root->left;
	while (l)
	{
		l = l->left;
		++hl;
	}

	auto r = root->right;
	while (r)
	{
		r = r->right;
		++hr;
	}

	if (hl == hr) // 如果左右子树高度相同，则是满二叉树，节点数 = 2^h - 1
	{
		return pow(2, hl) - 1;
	}

	// 否则递归求解
	return 1 + countNodes(root->left) + countNodes(root->right);
}