#pragma once
#include "TreeNode.h"
#include "../base_header.h"

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

/*
	扩展一
	给出的不是两个节点，而是一个数组
	求这个数组里的所有节点的最近公共祖先

	只需将判断当前节点的方式修改即可
*/

TreeNode* lowestCommonAncestor(TreeNode* root, const vector<TreeNode*>& nodes)
{
	if (!root)return nullptr;
	
	// 使用hash表加快搜索
	unordered_set<TreeNode*> set{ nodes.begin(), nodes.end() };
	
	auto dfs = [&](this auto&& dfs, TreeNode* node) -> TreeNode*
		{
			if (!node)return nullptr;
			if (set.contains(node))return node; // 改：node如果包含于给出的节点数组里，直接返回

			auto left = dfs(node->left);
			auto right = dfs(node->right);

			if (left || right)
			{
				return node;
			}

			return left ? left : right;
		};

	return dfs(root);
}

/*
	扩展二
	p、q可能不存在于给定的二叉树中
	如果二者都存在，返回最近公共祖先，否则返回空

	原本p和q都存在于二叉树中，所以找到任一一个便返回
	因为要么另一个在其他树中，之后一定会被遍历；要么另一个在子树中，那么自己就是公共祖先
	可是现在p和q可能不存在，所以必选完整地遍历二叉树才能确认“是否存在”这件事
	于是不能够在先序位置直接返回
*/

TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)
{
	bool found_p = false, found_q = false;
	auto dfs = [&](this auto&& dfs, TreeNode* node)->TreeNode*
		{
			if (!node)return nullptr;

			// 不可以在先序位置直接返回，因为要完整遍历，确认p和q是否存在
			// if (node == p || node == q)return node;

			auto left = lowestCommonAncestor2(node->left, p, q);
			auto right = lowestCommonAncestor2(node->right, p, q);
			if (left && right)
			{
				return node;
			}

			// 对于找到的节点，令其标记为true
			if (node == p || node == q)
			{
				if (node == p)found_p = true;
				if (node == q)found_q = true;
				return node;
			}

			return left ? left : right;
		};
	
	auto res = dfs(root);

	return found_q && found_p ? res : nullptr;
}

/*
	扩展三
	在二叉搜索树中寻找最近公共祖先

	由于是搜索树，所以要利用左小右大的性质才能更快地求解
	p和q的公共祖先是包含了它们两个的最小树的根节点
	并且一定存在于p和q的元素值组成的区间中
	而递归的性质，树的根节点一定是最先抵达的，所以无需关系p和q本身
	只需要遍历到第一个处于p, q区间的点返回即可
*/

TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q)
{
	auto Min = min(p->val, q->val);
	auto Max = max(p->val, q->val);
	auto dfs = [=](this auto&& dfs, TreeNode* node)->TreeNode*
		{
			if (!node)return nullptr;

			// 只要值处于区间内则是公共祖先，因为公共祖先一定是区间内最先遍历到的点
			if (node->val >= Min && node->val <= Max)return node;

			auto left = dfs(node->left);
			auto right = dfs(node->right);
			if (left && right)
			{
				return node;
			}

			return left ? left : right;
		};

	return dfs(root);
}