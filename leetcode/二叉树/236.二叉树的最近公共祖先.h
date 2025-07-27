#pragma once
#include "TreeNode.h"

/*
	难度：中等，经典
	给出二叉树的根节点和两个必定存在于二叉树中的节点p和q
	求这两个节点的最近公共祖先

	首先遍历二叉树，如果找到了p或q，就返回给递归的上一层
	因为对于找到的p点而言，q要么在它的子树里，此时p本身就是二者的最近公共祖先，要么在其他树里。
	由于所有树都会被遍历，所以q也会被返回，最终它们会在某个节点“交汇”作为递归左右子树的结果
	于是在后序位置判断递归结果就能知道此节点是否是最近公共祖先
	然后也同样直接返回最近公共祖先。因为“交汇”只会发生一次，所以最近公共祖先会一直被返回，直到根节点

*/

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
	if (!root)return nullptr;

	// 找到p或q，直接返回。此时可能p在q的子树里，那么q也就是答案，应该返回
	if (root == p || root == q)return root;

	// 在左右子树里找到了p和q，则当前节点就是最近公共祖先
	auto left = lowestCommonAncestor(root->left, p, q);
	auto right = lowestCommonAncestor(root->right, p, q);
	if (left && right)
	{
		return root;
	}

	// 在左右子树里，只找到里p或q的其中一个，又或者找到了答案，都可以直接返回
	// 如果返回的是答案，因为答案只有一个，所以永远满足不了上面的if
	// 所以答案会被一直返回，直到根节点
	return left ? left : right;
}