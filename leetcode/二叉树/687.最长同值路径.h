#pragma once
#include "../base_header.h"
#include "TreeNode.h"
/*
	�Ѷȣ��е�
	�������������ֵͬ��ɵ�·������󳤶�
	·�����Բ��������ڵ�

	����·�����Բ��������ڵ㣬���Ǵ𰸿�����ȫ����������
	�����Ѿ�֪�������������������ֵͬ�·��
	������Ҫ���Ӧ���ǣ����������ֵͬ�·�������������ֵͬ�·���������Լ���ֵͬ�·�������ߵ����ֵ
	���󾭹��Լ���ֵͬ�·����Ҫ�õ����������ӽڵ�Ϊĩβ��ֵͬ�·��
	Ȼ����������Խڵ��ֵ���Լ���ͬ������Խ�������ӵõ������Լ���ֵͬ�·��
	ͬʱ���轫�Լ����е�ֵͬ�·�������Լ�Ϊĩβ��ֵͬ�·�����ص���һ��ݹ���
*/

int longestUnivaluePath(TreeNode* root)
{
	auto recursion = [](this auto&& recursion, TreeNode* node)->pair<int, int> // �������ڵ�ֵͬ�·�������Լ�Ϊĩβ��ֵͬ�·��
		{
			if (!node)return { 0, 0 };

			auto left = recursion(node->left);
			auto right = recursion(node->right);

			int l1 = 1;
			int l2 = max(left.second, right.second);

			// ��ڵ����Լ���ȣ������Լ�Ϊĩβ��ֵͬ�·������ļ�һ
			if (node->left && node->left->val == node->val)
			{
				l1 = 1 + left.first;
			}

			// �ҽڵ����Լ���ȣ������Լ�Ϊĩβ��ֵͬ�·�����ҵļ�һ
			if (node->right && node->right->val == node->val)
			{
				l1 = max(l1, 1 + right.first);
			}

			// ���ҽڵ����Լ���ͬ�������ڵ�ֵͬ�·��������Ҽ�һ
			if (node->left && node->left->val == node->val
				&& node->right && node->right->val == node->val)
			{
				l2 = max(l2, 1 + left.first + right.first);
			}

			return { l1, max(l1, l2) };
		};

	return max(0, recursion(root).second - 1);
}