#pragma once
#include "TreeNode.h"
#include "../base_header.h"
/*
	�Ѷȣ��еȣ����ѣ�
	��n���ڵ�Ķ������У�ÿ���ڵ���node.val��Ӳ�ң����нڵ��ֵ�ĺ�Ϊn
	ÿ�ν�һ��Ӳ��Ų�����ڵĽڵ�
	�������ÿ���ڵ㶼��һ��Ӳ�ҵ�Ų����С����

	�൱����Ӳ�Ҿ����ڵ�����֮�ͣ�������������ǡ�ñ������нڵ�
	����ֻ��Ҫ֪����1ÿ���ڵ��Ƿ�ҪŲӲ�ң�2.ÿ���ڵ�ҪŲ���ٸ�Ӳ��
	�������
	�ֽ����⣬�����֪����������Ų������Ϊl��r
	���ڴ���ҪŲ������Ӳ�Һʹ���������Ų��Ӳ�����ֿ��ܣ����Էֱ�����������ʾ
	����ÿ���ڵ�ҪŲ���ٸ�Ӳ�Ҿ͵���Ų������Ӳ�Һʹ���������Ų����ֵ�ľ���ֵ
	��˿��Բ�����Ӳ�Ҹ�����ֻ��������һ���������Ӹ��ڵ������ȡ�������ݸ���������
	���仯����ֵ����ͨ���ýڵ��Ӳ�ҵ�����
*/

int distributeCoins(TreeNode* root)
{
	auto recursion = [](this auto&& recursion, TreeNode* node, int& coins)->int
		{
			if (!node)return 0;

			// �Լ�����һ��Ӳ�ң�����Ĵ��ݸ���������
			int c = coins + node->val - 1;
			auto left = recursion(node->left, c);
			auto right = recursion(node->right, c);

			auto ret = left + right + abs(coins - c); // ������Ų������ + ������Ų������ + Ӳ�ҵı仯�����ľ���ֵ
			coins = c;
			return ret;
		};

	int coins = 0;
	return recursion(root, coins);
}