#pragma once
#include "TreeNode.h"
#include "../base_header.h"
#include <climits>
/*
	难度：中等
	二叉搜索树中仅有两个节点的值交换，请互换两个值使二叉搜索树恢复

	不是互换节点，所以不复杂
	二叉搜索树中序遍历是有序的，所以代码一定位于中序位置
	两个值互换时，会发生两次前值大于后值
	第一次时，前值是错的
	第二次时，后值是错的
	所以用两个指针找到两个节点即可

	要注意可能是递增序列上的相邻的两个值互换了，所以可能只存在一次前值大于后值的情况
	因此前值只在空时初次设置，后值则总是设置
*/

void recoverTree(TreeNode* root) {
	TreeNode* _1 = nullptr, * _2 = nullptr;
	TreeNode n{ INT_MIN };
	TreeNode* previous = &n;// 让previous指向一个局部结点，如此就无需判空了
	auto recursion = [&](this auto&& recursion, TreeNode* node)
		{
			if (!node)return;
			recursion(node->left);

			if (previous->val > node->val)
			{
				if (!_1)_1 = previous; // 前值只在空时设置

				_2 = node;//后值总是设置，为node。因为可能只发生一次
			}
			previous = node;
			recursion(node->right);
		};
	recursion(root);
	swap(_1->val, _2->val);
}