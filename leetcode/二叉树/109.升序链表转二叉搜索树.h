#pragma once
#include "TreeNode.h"
/*
	�Ѷȣ��е�
	����������תΪ����������
	���ڶ���������Ҫ�����������߶Ȳ����1
	����Ӧ�þ����ܵ���������е�Ϊ����Ȼ���ڵݹ�����������δ��������������ַ�
	�ڵݹ��ͬʱ�������������ÿ������ڵ��ֵ�������Ľڵ�
	������Ҫʹ��������������Ľڵ����������ڵ��˳��һ��
*/

struct ListNode 
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	
};

TreeNode* sortedListToBST(ListNode* head) {
	// �����������
	auto node = head;
	auto len = 0;
	while (node)
	{
		node = node->next;
		++len;
	}

	// �ݹ鴴���������������ͬʱ��������ʹ˳��һ��
	auto cur = head;
	auto dfs = [&cur](this auto&& dfs, int l, int r)->TreeNode*
		{
			if (l >= r)return nullptr;

			int mid = (l + r) / 2;
			auto left = dfs(l, mid);

			auto node = new TreeNode{ cur->val, left, nullptr };
			cur = cur->next;
			node->right = dfs(mid + 1, r);

			return node;
		};

	return dfs(0, len);
}