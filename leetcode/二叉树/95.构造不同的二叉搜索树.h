#pragma once
#include "../base_header.h"

namespace q95
{
/*
	�Ѷȣ��е�
	��������n�������������1~n���ɵĶ���������

	ÿ��ֵ��������Ϊ���ڵ㣬Ȼ�����С�ı�Ȼ���ڹ���������
	������ı�Ȼ���ڹ������������ݹ鼴��
	������ͬ�ĸ��ڵ㣬����������ͬ��Ϊ��ͬ�Ķ������������������������ṹ
	�Ե����Ϲ�������п��ܵ��������ڹ�������п��ܵ���
*/

struct TreeNode
{
	int val = 0;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

vector<TreeNode*> build(int lo, int hi)
{
	// ��������ȥ����
	vector<TreeNode*> ans;
	// �������Ϊ�գ������һ���սڵ㣬ʹ���ڵ�������1�п��ܵ���������������
	if (lo > hi)
	{
		ans.push_back(nullptr);
		return ans;
	}

	// lo��hi֮���ÿ��ֵ��������Ϊ���ڵ㣬ȷ�����ڵ��ֵi
	// �ȵݹ�ȥ����������[lo, i-1] �������� [i+1, hi] �����п���
	// ��ô��iΪ���Ķ��������������п��ܣ������������Ŀ��� * �������Ŀ���
	for (int i = lo; i <= hi; ++i)
	{
		auto leftTree = build(lo, i - 1);
		auto rightTree = build(i + 1, hi);

		for (auto& left : leftTree)
		{
			for (auto& right : rightTree)
			{
				auto node = new TreeNode{ i, left, right };
				ans.push_back(node);
			}
		}
	}

	return ans;
}

vector<TreeNode*> generateTrees(int n) {
	return build(1, n);
}
}