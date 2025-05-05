#pragma once
#include "leetcode/base_header.h"

// 标准的二分法框架
int binary_search(const vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size();
	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (nums[mid] < target)
		{
			l = mid + 1;
		}
		else if (nums[mid] > target)
		{
			r = mid;
		}
		else
		{
			return mid; // 注意此处不是return l
		}
	}

	return l;
}

/*
	何时while (l < r)，何时while (l <= r)？
		取决与使用何种区间，r = nums.size()，还是 r = nums.size() - 1
		while是用于判断区间内还有无元素的，如果是前闭后开区间，l < r表示还有区间内还有元素
		如果是前闭后闭区间，l<=r表示区间内还有元素
		同理 r = mid 还是 r = mid-1 也由区间决定

		建议使用前闭后开，个别题目才需要前闭后闭
*/

/* 
	寻找左边界（第一个不小于target）的框架
	主要区别是 nums[mid] == target 时，也要收缩右界
	因为mid的左右两边都可能存在重复元素，而由于找的是左界
	所以不小于时都收缩右界
	口诀：求左界不停收右界
 */
int lower_bound(const vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size();
	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (nums[mid] < target)
		{
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}

	return l;
}

/*
	寻找右边界的下一个元素（第一个大于target）的框架
	nums[mid] == target 时，也要收缩左界
	注意：返回的是右边界的下一个元素 / 第一个严格大于target的元素
	所以如果要有边界，还需减1
 */
int higher_bound(const vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size();
	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (nums[mid] > target)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}

	return l;
}

/*
	二分法的适用范围
	1.有序的数组
	2.隐含单调关系的方程：答案关于某个自变量呈单调关系，而这个自变量的区间可以确定
	
	常见的题目描述
	1.查找定值
	2.在单调关系里找左右边界
*/