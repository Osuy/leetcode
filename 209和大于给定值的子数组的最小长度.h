#pragma once
#include <vector>
using std::vector;
/*
	求和大于等于target的子数组的最小长度
	
	难度：中等

	子数组是连续的，可以想到用滑动窗口。条件是和大于等于target，和是累加计算得出到
	所以只能是同相双指针
	右界前进，和如果大于等于target，则ans = min(ans, r-l). 然后左界前进，直到和小于target或与右界相遇

	右界前进到数组末尾时，上一个循环要么和还是小于target，要么左界收拢了
		无论哪样，没有新元素，和不会再变大了，所以循环退出的条件时右界到达末尾

	类似的还有713 3
*/

class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		int ans = 1e5 + 1;
		int sum = 0;
		int size = nums.size();
		int l = 0, r = 0;// 左闭右开区间，子数组的长度 = r - l.不用加1
		while (r < size)
		{
			sum += nums[r++];
			while (l < r && sum >= target)
			{
				ans = std::min(ans, r - l);
				sum -= nums[l++];
			}
		}

		return ans == 1e5 + 1 ? 0 : ans;
	}
};