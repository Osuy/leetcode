#pragma once
#include "../../base_header.h"
/*
	难度：中等
	将无序数组的子数组排序就能使整个数组有序，求这样的子数组的最小长度

	单调栈解法：
	正序遍历维护递增栈，出栈的元素是无序元素，里面的最靠前的就是数组的无序区间左界
	逆序遍历维护递减栈，里面最靠后的就是无序区间的右界
*/
int findUnsortedSubarray(vector<int>& nums) 
{
	int n = nums.size();
	int left = INT_MAX, right = INT_MIN;
	// 递增栈，存储元素索引
	stack<int> incrStk;
	for (int i = 0; i < n; i++) 
	{
		while (!incrStk.empty() && nums[incrStk.top()] > nums[i]) 
		{
			// 弹出的元素都是乱序元素，其中最小的索引就是乱序子数组的左边界
			left = min(left, incrStk.top());
			incrStk.pop();
		}
		incrStk.push(i);
	}
	// 递减栈，存储元素索引
	stack<int> decrStk;
	for (int i = n - 1; i >= 0; i--) 
	{
		while (!decrStk.empty() && nums[decrStk.top()] < nums[i]) 
		{
			// 弹出的元素都是乱序元素，其中最大的索引就是乱序子数组的右边界
			right = max(right, decrStk.top());
			decrStk.pop();
		}
		decrStk.push(i);
	}
	if (left == INT_MAX && right == INT_MIN) 
	{
		// 说明单调栈没有弹出任何元素，即 nums 本来就是有序的
		return 0;
	}
	return right - left + 1;
}

/*
	前缀最大值解法
	一个有序数组 的前缀最大值和后缀最小值是相等的
	而对于一个无序数组，它的前缀最大值和后缀最小值的 第一个以及最后一个不同的元素构成的区间
	就是无序区间
*/
int findUnsortedSubarray(vector<int>& nums) 
{

	auto premax = nums, postmin = nums;
	for (int i = 1;i < nums.size();++i)
	{
		premax[i] = max(premax[i - 1], premax[i]);
	}

	for (int i = nums.size() - 2;i >= 0;--i)
	{
		postmin[i] = min(postmin[i + 1], postmin[i]);
	}

	int l = 0, r = nums.size() - 1;
	while (l < nums.size() && premax[l] == postmin[l])++l;
	while (r >= l && premax[r] == postmin[r])--r;

	return  r - l + 1;

}