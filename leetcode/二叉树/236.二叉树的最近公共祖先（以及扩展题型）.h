#pragma once
#include "TreeNode.h"
#include "../base_header.h"

/*
	�Ѷȣ��еȣ�����
	�����������ĸ��ڵ�������ض������ڶ������еĽڵ�p��q
	���������ڵ�������������

	���ȱ���������������ҵ���p��q���ͷ��ظ��ݹ����һ��
	��Ϊ�����ҵ���p����ԣ�qҪô�������������ʱp������Ƕ��ߵ�����������ȣ�Ҫô���������
	�������������ᱻ����������qҲ�ᱻ���أ��������ǻ���ĳ���ڵ㡰���㡱��Ϊ�ݹ����������Ľ��
	�����ں���λ���жϵݹ�������֪���˽ڵ��Ƿ��������������
	Ȼ��Ҳͬ��ֱ�ӷ�������������ȡ���Ϊ�����㡱ֻ�ᷢ��һ�Σ���������������Ȼ�һֱ�����أ�ֱ�����ڵ�

*/

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
	if (!root)return nullptr;

	// �ҵ�p��q��ֱ�ӷ��ء���ʱ����p��q���������ôqҲ���Ǵ𰸣�Ӧ�÷���
	if (root == p || root == q)return root;

	// �������������ҵ���p��q����ǰ�ڵ���������������
	auto left = lowestCommonAncestor(root->left, p, q);
	auto right = lowestCommonAncestor(root->right, p, q);
	if (left && right)
	{
		return root;
	}

	// �����������ֻ�ҵ���p��q������һ�����ֻ����ҵ��˴𰸣�������ֱ�ӷ���
	// ������ص��Ǵ𰸣���Ϊ��ֻ��һ����������Զ���㲻�������if
	// ���Դ𰸻ᱻһֱ���أ�ֱ�����ڵ�
	return left ? left : right;
}

/*
	��չһ
	�����Ĳ��������ڵ㣬����һ������
	���������������нڵ�������������

	ֻ�轫�жϵ�ǰ�ڵ�ķ�ʽ�޸ļ���
*/

TreeNode* lowestCommonAncestor(TreeNode* root, const vector<TreeNode*>& nodes)
{
	if (!root)return nullptr;
	
	// ʹ��hash��ӿ�����
	unordered_set<TreeNode*> set{ nodes.begin(), nodes.end() };
	
	auto dfs = [&](this auto&& dfs, TreeNode* node) -> TreeNode*
		{
			if (!node)return nullptr;
			if (set.contains(node))return node; // �ģ�node��������ڸ����Ľڵ������ֱ�ӷ���

			auto left = dfs(node->left);
			auto right = dfs(node->right);

			if (left || right)
			{
				return node;
			}

			return left ? left : right;
		};

	return dfs(root);
}

/*
	��չ��
	p��q���ܲ������ڸ����Ķ�������
	������߶����ڣ���������������ȣ����򷵻ؿ�

	ԭ��p��q�������ڶ������У������ҵ���һһ���㷵��
	��ΪҪô��һ�����������У�֮��һ���ᱻ������Ҫô��һ���������У���ô�Լ����ǹ�������
	��������p��q���ܲ����ڣ����Ա�ѡ�����ر�������������ȷ�ϡ��Ƿ���ڡ������
	���ǲ��ܹ�������λ��ֱ�ӷ���
*/

TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)
{
	bool found_p = false, found_q = false;
	auto dfs = [&](this auto&& dfs, TreeNode* node)->TreeNode*
		{
			if (!node)return nullptr;

			// ������������λ��ֱ�ӷ��أ���ΪҪ����������ȷ��p��q�Ƿ����
			// if (node == p || node == q)return node;

			auto left = lowestCommonAncestor2(node->left, p, q);
			auto right = lowestCommonAncestor2(node->right, p, q);
			if (left && right)
			{
				return node;
			}

			// �����ҵ��Ľڵ㣬������Ϊtrue
			if (node == p || node == q)
			{
				if (node == p)found_p = true;
				if (node == q)found_q = true;
				return node;
			}

			return left ? left : right;
		};
	
	auto res = dfs(root);

	return found_q && found_p ? res : nullptr;
}

/*
	��չ��
	�ڶ�����������Ѱ�������������

	������������������Ҫ������С�Ҵ�����ʲ��ܸ�������
	p��q�Ĺ��������ǰ�����������������С���ĸ��ڵ�
	����һ��������p��q��Ԫ��ֵ��ɵ�������
	���ݹ�����ʣ����ĸ��ڵ�һ�������ȵִ�ģ����������ϵp��q����
	ֻ��Ҫ��������һ������p, q����ĵ㷵�ؼ���
*/

TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q)
{
	auto Min = min(p->val, q->val);
	auto Max = max(p->val, q->val);
	auto dfs = [=](this auto&& dfs, TreeNode* node)->TreeNode*
		{
			if (!node)return nullptr;

			// ֻҪֵ�������������ǹ������ȣ���Ϊ��������һ�������������ȱ������ĵ�
			if (node->val >= Min && node->val <= Max)return node;

			auto left = dfs(node->left);
			auto right = dfs(node->right);
			if (left && right)
			{
				return node;
			}

			return left ? left : right;
		};

	return dfs(root);
}