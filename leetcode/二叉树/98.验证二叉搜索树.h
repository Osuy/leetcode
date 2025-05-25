#pragma once
#include "TreeNode.h"
/*
	难度：困难

	二叉搜索树并不只满足 根节点大于左孩子而小于右孩子
	而是要满足：根节点大于左子树的最大值，小于右子树的最小值，因此需要额外的变量去维护
*/
namespace q98
{


bool isValidBST(TreeNode* root)
{
	auto is_bst = [](this auto&& is_bst, TreeNode* root, int& min, int& max)
		{
			if (!root)return true;

			min = max = root->val;
			int lmax = root->val, rmin = root->val;
			auto ans = (!root->left || (is_bst(root->left, min, lmax) && lmax < root->val))
				&& (!root->right || (is_bst(root->right, rmin, max) && root->val < rmin));

			return ans;
		};
	int min, max;
	return is_bst(root, min, max);
}
}