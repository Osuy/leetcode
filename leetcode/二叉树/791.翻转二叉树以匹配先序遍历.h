#pragma once
#include "../base_header.h"
#include "TreeNode.h"
/*
	�Ѷȣ��е�
	����һ����������һ������
	�������Ľڵ��������鳤�ȶ�Ϊn���ҽڵ��ֵ������Ԫ�ض�Ϊ1~n�һ�����ͬ
	����������ת���ֽڵ㣬ʹ�����������������ͬ
	����޷���ת�õ����������-1

	���⽨����226.��ת�������Ļ����ϣ�����Ҫ��������
	����indexָ��ǰnode��Ӧ������λ��
	���nums[index] ��= node->val ���޷���ת�ɹ������� -1
	��� node->left && nums[index + 1] ��= node->left->val������ڵ�������ֵ��ƥ�䣬���䷭ת
		���ڷ�ת���ҽڵ��Ƿ�ƥ�䣬������֤�������ݹ�

*/

vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage)
{
	int index = 0;
	vector<int> ans;
	auto recursion = [&](this auto&& recursion, TreeNode* node)->bool
		{
			if (!node)return true;
			if (voyage[index] != node->val)
			{
				return false;
			}
			++index;
			if (node->left && node->left->val != voyage[index])
			{
				swap(node->left, node->right);
				ans.push_back(node->val);
			}
			return recursion(node->left) && recursion(node->right);
		};

	return recursion(root) ? ans : vector<int>{ -1 };
}