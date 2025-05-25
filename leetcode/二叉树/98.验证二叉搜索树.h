#pragma once
#include "TreeNode.h"
/*
	�Ѷȣ�����

	��������������ֻ���� ���ڵ�������Ӷ�С���Һ���
	����Ҫ���㣺���ڵ���������������ֵ��С������������Сֵ�������Ҫ����ı���ȥά��
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