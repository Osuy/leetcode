#pragma once
#include "base_header.h"

/*
	难度：中等
	求数组的子数组的元素乘积小k的数量

	考虑输入：数组长度尾10^4，且无需，所以用双指针。数组所有元素为正，可以用滑动窗口
	如果一个子[i, j)的乘积小于k，则它的子数组的乘积也小于k，数量一共是j-i
	于是滑动窗口右界扩大乘积，当乘积大于k时，左界右移缩小乘积。得到恰好乘积小于k的区间[i,j)
	ans+=j-i
		
*/
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
	if (k == 0)return 0;
	int ans = 0;
	int mul = 1;
	int size = nums.size();
	int l = 0, r = 0;

	while (r < size)
	{
		mul *= nums[r++];
		while (mul >= k && l < r)
		{
			mul /= nums[l++];
		}
		ans += r - l;
	}

	return ans;
}