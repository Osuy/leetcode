#pragma once
#include "../base_header.h"
/*
	难度：中等
	给定一棵无限节点的二叉树，节点的值为自然数，从1开始之字形递增，
	即：视从左到右为正方向，每一层交替正负方向排列节点
	对给出的数n，求从根节点到该节点的路径

	如果没有之字形排列，则1的子节点为2、3
	2的子节点为4、5...
	i的子节点为2*i、2*i+1

	于是只要将n不停地除以2，就得到了路径上的点
	但是由于之字形排列，i的父节点被替换为同一层的其他节点
	注意到每一层的节点数可以计算，父节点与被替换的父节点之和就是该层数最大最小值之和
	再者：
		第i层的节点数是2的i次方（根节点视为0层）
		第0~i-1层的节点数是2的i次方-1
		于是第i层的最小值是2的i次方
		第i层的最大值 = 第i+1层的最小值-1
*/

vector<int> pathInZigZagTree(int label) {
	vector<int> ans;

	int l = label;
	int hight = 0;
	while (l)
	{
		l >>= 1;
		++hight;
	}

	while (label > 1)
	{
		ans.push_back(label);
		--hight;
		label = (1 << (hight - 1)) + (1 << hight) - 1 - (label >> 1);
	}

	ans.push_back(1);
	reverse(ans.begin(), ans.end());
	return ans;
}