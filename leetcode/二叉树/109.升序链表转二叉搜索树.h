#pragma once
#include "TreeNode.h"
/*
	难度：中等
	将升序链表转为二叉搜索树
	由于二叉搜索树要求左右子树高度差不超过1
	所以应该尽可能地以链表的中点为根，然后在递归地在左右两段创建子树，即二分法
	在递归的同时还需遍历链表，以每个链表节点的值创建树的节点
	所以需要使用中序遍历，树的节点才能与链表节点的顺序一样
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
	// 先求出链表长度
	auto node = head;
	auto len = 0;
	while (node)
	{
		node = node->next;
		++len;
	}

	// 递归创建，中序遍历树的同时遍历链表，使顺序一样
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