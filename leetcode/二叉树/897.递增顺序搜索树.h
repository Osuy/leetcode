#pragma once
#include "TreeNode.h"
/*
	难度：简单
	把一棵搜索树转为只有右节点的搜索树
	即：结构上类似但链表，每个节点只有右节点，且保持右节点比自己大
	
	虽然是简单题，但需要拆分理解递归分解问题的思路
	对于每个节点而言，把他的左右子树转化完后，它自己所处的位置应该是：
	转化完的左子树的根left的最右下方，并把转化完的右子树的根节点作为右节点

	代码大约是：
		auto left = build(node->left);
		node->right = build(node->right);
	右节点可以直接赋值，但是由于不能有左节点，所以要置空：
		node->left = nullptr;

	最后node自己要插入到left的最右下。但是目前获取不到这个节点，要么自己再循环找到该节点
	要么利用递归，把node传入build(node->left)里
	
	于是build不仅负责把树转化，还负责把第二参数放到最右下
	考虑如何放到最右下呢？
	当node没有右孩子时，说明以及到了最右下了，于是无需node->right = build(node->right);
	而是node->right = 第二参数

	但是换一个角度想：如果不存在右子树，而由又一个参数要插入到右子树的最右下
	那么直接返回该参数即可

	最终简化如下
*/

TreeNode* increasingBST(TreeNode* root, TreeNode* right = nullptr)
{
	if (!root)return right; // 本树为空，直接返回right

	auto left = increasingBST(root->left, root); // 对左子树，要把自己插入到其最右下
	root->left = nullptr;
	root->right = increasingBST(root->right, right);// 对右子树，要把第二参数插入到其最右下

	return left;
}