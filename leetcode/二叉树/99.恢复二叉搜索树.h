#pragma once
#include "TreeNode.h"
#include "../base_header.h"
#include <climits>
/*
	�Ѷȣ��е�
	�����������н��������ڵ��ֵ�������뻥������ֵʹ�����������ָ�

	���ǻ����ڵ㣬���Բ�����
	�����������������������ģ����Դ���һ��λ������λ��
	����ֵ����ʱ���ᷢ������ǰֵ���ں�ֵ
	��һ��ʱ��ǰֵ�Ǵ��
	�ڶ���ʱ����ֵ�Ǵ��
	����������ָ���ҵ������ڵ㼴��

	Ҫע������ǵ��������ϵ����ڵ�����ֵ�����ˣ����Կ���ֻ����һ��ǰֵ���ں�ֵ�����
	���ǰֵֻ�ڿ�ʱ�������ã���ֵ����������
*/

void recoverTree(TreeNode* root) {
	TreeNode* _1 = nullptr, * _2 = nullptr;
	TreeNode n{ INT_MIN };
	TreeNode* previous = &n;// ��previousָ��һ���ֲ���㣬��˾������п���
	auto recursion = [&](this auto&& recursion, TreeNode* node)
		{
			if (!node)return;
			recursion(node->left);

			if (previous->val > node->val)
			{
				if (!_1)_1 = previous; // ǰֵֻ�ڿ�ʱ����

				_2 = node;//��ֵ�������ã�Ϊnode����Ϊ����ֻ����һ��
			}
			previous = node;
			recursion(node->right);
		};
	recursion(root);
	swap(_1->val, _2->val);
}