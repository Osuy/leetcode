#pragma once
#include "base_header.h"
/*
	难度：中等
	类型：二分查找
	题目描述：
		给你一个按照非递减顺序排列的整数数组 nums ，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
		如果数组中不存在目标值 target ，返回 [-1, -1]。
		你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

	分析：两次二分查找分别找出左右
*/

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) 
	{
		// 数组空、数组的最大值小于taget、数组的最小值大于target，都不符合条件，return
		if (nums.empty() || target < nums.front() || nums.back() < target)
		{
			return { -1, -1 };
		}

		int l = 0;
		int r = nums.size() - 1;

		int res_r = (l + r) >> 1;
		while (l < r)
		{
			if (nums[res_r] <= target)
			{
				l = res_r;
				res_r = ((1 + l + r) >> 1);
			}
			else
			{
				r = res_r - 1;
				res_r = (l + r) >> 1;
			}
		}

		l = 0;
		r = res_r;
		int res_l = (l + r) >> 1;
		while (l < r)
		{
			if (target <= nums[res_l])
			{
				r = res_l;
				res_l = ((l + r) >> 1);
			}
			else
			{
				l = res_l + 1;
				res_l = (l + r) >> 1;
			}
		}

		if (target == nums[res_l] && target == nums[res_r])
		{
			return { res_l, res_r };
		}

		return { -1, -1 };
	}
};