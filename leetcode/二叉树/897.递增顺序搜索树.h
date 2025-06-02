#pragma once
#include "TreeNode.h"
/*
	�Ѷȣ���
	��һ��������תΪֻ���ҽڵ��������
	�����ṹ�����Ƶ�����ÿ���ڵ�ֻ���ҽڵ㣬�ұ����ҽڵ���Լ���
	
	��Ȼ�Ǽ��⣬����Ҫ������ݹ�ֽ������˼·
	����ÿ���ڵ���ԣ���������������ת��������Լ�������λ��Ӧ���ǣ�
	ת������������ĸ�left�������·�������ת������������ĸ��ڵ���Ϊ�ҽڵ�

	�����Լ�ǣ�
		auto left = build(node->left);
		node->right = build(node->right);
	�ҽڵ����ֱ�Ӹ�ֵ���������ڲ�������ڵ㣬����Ҫ�ÿգ�
		node->left = nullptr;

	���node�Լ�Ҫ���뵽left�������¡�����Ŀǰ��ȡ��������ڵ㣬Ҫô�Լ���ѭ���ҵ��ýڵ�
	Ҫô���õݹ飬��node����build(node->left)��
	
	����build�����������ת����������ѵڶ������ŵ�������
	������ηŵ��������أ�
	��nodeû���Һ���ʱ��˵���Լ������������ˣ���������node->right = build(node->right);
	����node->right = �ڶ�����

	���ǻ�һ���Ƕ��룺�����������������������һ������Ҫ���뵽��������������
	��ôֱ�ӷ��ظò�������

	���ռ�����
*/

TreeNode* increasingBST(TreeNode* root, TreeNode* right = nullptr)
{
	if (!root)return right; // ����Ϊ�գ�ֱ�ӷ���right

	auto left = increasingBST(root->left, root); // ����������Ҫ���Լ����뵽��������
	root->left = nullptr;
	root->right = increasingBST(root->right, right);// ����������Ҫ�ѵڶ��������뵽��������

	return left;
}