#pragma once
#include "TreeNode.h"
#include "../base_header.h"
/*
	�Ѷȣ�����
	����һ����ؿ��Ը���һ���ڵ�������ӽڵ㡢���ڵ�
	��һ����������ȫ���ǵ�����������

	�󾡿����ٵļ��������Ҫ�����ܵ���߼�ص�������
	��ͨ�ڵ��Ƿ�װ����޷�ȷ�������ڵ㰲װ�����ʸߣ�Ҷ�ӽڵ�ĸ��ڵ㰲װҲ�����������
	���ǵ����ڵ�ֻ��һ����Ҷ�ӽڵ�����Ϊ1�����������ȿ���Ҷ�ӽڵ�ĸ��ڵ㰲װ��أ�Ȼ��ݹ������
	���2���ڵ㰲װ

	������Ҫ���������ÿ���ڵ���Ҫ�����Ӽ���ص�ʣ�����:
		�սڵ㲻��Ҫ����
		Ҷ�ӽڵ���Ҫ���ǣ�������Ҫ��װ��ʣ�����Ϊ0
		Ҷ�ӽڵ�ĸ��ڵ��Ӻ�������λ�õõ�һ��0�����԰�װ��أ�Ȼ�󷵻�2
		��ͨ�ڵ㣬���ԴӺ�������λ�õõ�0��1��2����ֵ��������0��װ���
		1˵���ӽڵ㱻���ǣ����Լ��������ǣ������ø��ڵ㸲�ǣ�����0
		2˵���ӽڵ㰲װ���Լ������Ƿ���1

*/

int minCameraCover(TreeNode* root) {

	//if(!root)return 0;
	auto recursion = [](this auto&& recursion, TreeNode* node)->pair<int, int>
		{
			if (!node)return { 0, -1 };
			if (!node->left && !node->right)
			{
				return { 0,0 };
			}

			auto left = recursion(node->left);
			auto right = recursion(node->right);

			if (left.second == 0 || right.second == 0)
			{
				return { left.first + right.first + 1, 2 };
			}

			return { left.first + right.first, max(left.second, right.second) - 1 };
		};

	auto ans = recursion(root);
	if (ans.second == 0)++ans.first;
	return ans.first;
}