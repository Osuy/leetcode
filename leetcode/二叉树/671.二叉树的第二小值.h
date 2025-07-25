#pragma once
#include "TreeNode.h"
#include "../base_header.h"

/*
	难度：简单
	一个二叉树，每个节点只有0或2个子节点，且节点的值 = min(左右子节点的值)，左右子节点的值可以相等
	求二叉树的第二小值

	首先根节点为空，或根节点没有子节点，则无第二小值，返回-1
	其次根节点与子节点的值 = 子节点的较小者，假若子节点的值星等，则题目等价于递归求子树的第二小值中的较小者
	由于其中一个子树可能会返回-1，会比真正的第二小值更小。此时只要将-1转为无符号就能正常比较
	当两个子节点的数值不同时，较大的那个就是候选的第二小值，但是还需和另一子节点的递归求第二小值的结果比较
*/

int findSecondMinimumValue(TreeNode* root) {
	// 为空或无子节点，-1
	if (!root)return -1;
	if (!root->left)return -1;

	// 求左右子树的第二小值，可能返回-1，所以转为无符号整型
	auto lm = (unsigned)findSecondMinimumValue(root->left);
	auto rm = (unsigned)findSecondMinimumValue(root->right);

	// 如果子节点值相等，取子树的第二小值的较小者
	if (root->left->val == root->right->val)
	{
		return min(lm, rm);
	}
	// 如果右节点大，则候选，与左子树的第二小值比较
	else if (root->left->val < root->right->val)
	{
		return min(lm, (unsigned)root->right->val);
	}
	// 如果左节点大，则候选，与右子树的第二小值比较
	else
	{
		return min((unsigned)root->left->val, rm);
	}
}