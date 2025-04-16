#pragma once
#include "base_header.h"

/*
	双重循环解法可以解决

	如果要用滑动窗口，需要认识到，每向右滑动一格，窗口内的子数组的数量是 j-i+1
	因为对于新进入窗口的元素 el[j]，新增加的子数组有：
		1.el[j]
		2.el[j-1],el[j]
		...
		el[i],el[i+1]...el[j-1l,el[j]
		数量为 j-i+1
		
*/
class Solution {
public:
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
};