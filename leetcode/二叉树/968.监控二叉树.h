#pragma once
#include "TreeNode.h"
#include "../base_header.h"
/*
	难度：困难
	假设一个监控可以覆盖一个节点的自身、子节点、父节点
	求一个二叉树完全覆盖的所需监控数量

	求尽可能少的监控数量，要尽可能地提高监控地利用率
	普通节点是否安装监控无法确定，根节点安装利用率高，叶子节点的父节点安装也能提高利用率
	考虑到根节点只有一个，叶子节点至少为1个，所以优先考虑叶子节点的父节点安装监控，然后递归地向上
	间隔2个节点安装

	所以需要后序遍历，每个节点需要返回子集监控地剩余距离:
		空节点不需要覆盖
		叶子节点需要覆盖，但不需要安装，剩余距离为0
		叶子节点的父节点会从后续遍历位置得到一个0，所以安装监控，然后返回2
		普通节点，可以从后续遍历位置得到0、1、2三种值，其中有0则安装监控
		1说明子节点被覆盖，但自己不被覆盖，可以让父节点覆盖，返回0
		2说明子节点安装，自己被覆盖返回1

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