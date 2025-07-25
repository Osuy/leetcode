#pragma once
#include "TreeNode.h"
#include "../base_header.h"

/*
	�Ѷȣ���
	һ����������ÿ���ڵ�ֻ��0��2���ӽڵ㣬�ҽڵ��ֵ = min(�����ӽڵ��ֵ)�������ӽڵ��ֵ�������
	��������ĵڶ�Сֵ

	���ȸ��ڵ�Ϊ�գ�����ڵ�û���ӽڵ㣬���޵ڶ�Сֵ������-1
	��θ��ڵ����ӽڵ��ֵ = �ӽڵ�Ľ�С�ߣ������ӽڵ��ֵ�ǵȣ�����Ŀ�ȼ��ڵݹ��������ĵڶ�Сֵ�еĽ�С��
	��������һ���������ܻ᷵��-1����������ĵڶ�Сֵ��С����ʱֻҪ��-1תΪ�޷��ž��������Ƚ�
	�������ӽڵ����ֵ��ͬʱ���ϴ���Ǹ����Ǻ�ѡ�ĵڶ�Сֵ�����ǻ������һ�ӽڵ�ĵݹ���ڶ�Сֵ�Ľ���Ƚ�
*/

int findSecondMinimumValue(TreeNode* root) {
	// Ϊ�ջ����ӽڵ㣬-1
	if (!root)return -1;
	if (!root->left)return -1;

	// �����������ĵڶ�Сֵ�����ܷ���-1������תΪ�޷�������
	auto lm = (unsigned)findSecondMinimumValue(root->left);
	auto rm = (unsigned)findSecondMinimumValue(root->right);

	// ����ӽڵ�ֵ��ȣ�ȡ�����ĵڶ�Сֵ�Ľ�С��
	if (root->left->val == root->right->val)
	{
		return min(lm, rm);
	}
	// ����ҽڵ�����ѡ�����������ĵڶ�Сֵ�Ƚ�
	else if (root->left->val < root->right->val)
	{
		return min(lm, (unsigned)root->right->val);
	}
	// �����ڵ�����ѡ�����������ĵڶ�Сֵ�Ƚ�
	else
	{
		return min((unsigned)root->left->val, rm);
	}
}