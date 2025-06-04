#pragma once
#include "TreeNode.h"
/*
	�Ѷȣ�����
	��������еĶ�����������Ԫ�غ͵����ֵ
	����Ľⷨ��Ҫ������98.��֤������������
	�ڱ���������ͬʱ���õ���������ȥ��¼����Ԫ�غ�

	���ڲ�Ҫ�������Ƕ���������������ȥѰ�ҿ��ܴ��ڵĶ���������
	����������������Ƕ�������������ȻҪȥ�ݹ�������
*/
namespace q1373
{
int maxSumBST(TreeNode* root) 
{
	int ans = 0;

	auto recursion = [&ans](this auto&& recursion, TreeNode* node, int& min, int& max, int& sum) ->bool
		{
			if (!node)return true;
			int lmax = node->val, rmin = node->val;
			min = max = node->val;
			int lsum = 0, rsum = 0;
			// ����������Ҫ�ݹ飬�������������Ƕ���������
			auto rl = recursion(node->left, min, lmax, lsum);
			auto rr = recursion(node->right, rmin, max, rsum);

			const bool is_bst = rl && rr
				&& (!node->left || lmax < node->val)
				&& (!node->right || rmin > node->val);

			if (is_bst)
			{
				sum = node->val + lsum + rsum;
				ans = std::max(ans, sum);
			}
			return is_bst;
		};

	int min, max, sum;
	recursion(root, min, max, sum);

	return ans;
}
}