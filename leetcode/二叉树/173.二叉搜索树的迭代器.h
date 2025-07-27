#pragma once
#include "TreeNode.h"
#include "../base_header.h"

/*
	难度：中等
	设计一个类作为二叉搜索树的迭代器，他能以中序遍历二叉树

	可是使用通用的二叉树迭代法：左分支栈
	左分支栈就是先入栈根节点，然后不断入栈栈顶的左子节点，直至null
	遍历时，出栈一个节点，如果节点存在右子节点，入栈，然后执行左分支栈的操作
	直至栈空
	入栈的顺序时前序遍历，出栈的顺序是中序遍历，如果希望得到后序遍历，可以使用右分支栈的入栈顺序的逆序

	为什么左分支栈能遍历二叉树？
	首先，左分支栈一定能遍历根节点和所有左子节点
	其次，对于一个右子节点，他的父亲要么是根节点，要么是左子节点，要么是右子节点
	而根据左分支栈出战后会入栈右子节点的规则，如果右子节点的父亲被遍历，它自己也能被遍历
	所以除了父节点是右子节点的右子节点，其他右子节点都会被遍历，进而，这些右子节点的右子节点也一定会被遍历
	所以，只剩下根节点的右分支。而根节点也会被遍历，所以其右分支也会被遍历
	于是根节点、所有左子节点、所有右子节点都会被遍历
*/

class BSTIterator {
	stack<TreeNode*> nodes;
public:
	BSTIterator(TreeNode* root)
	{
		while (root)
		{
			nodes.push(root);
			root = root->left;
		}
	}

	int next() {
		auto node = nodes.top();
		nodes.pop();

		auto right = node->right;
		while (right)
		{
			nodes.push(right);
			right = right->left;
		}

		return node->val;
	}

	bool hasNext() {
		return !nodes.empty();
	}
};