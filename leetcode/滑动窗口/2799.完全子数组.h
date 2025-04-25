#pragma once
#include "../base_header.h"
/*
	难度：中等
	如果一个子数组里出现了数组里所有的元素，则称为完全子数组
	求数组的完全子数组的个数

	本题的核心在于统计完全子数组的个数。并不需要求出所有的子数组再去验证子数组是否为完全子数组
	因为如果一个子数组[i, j]是完全子数组，则[i, j+1]、[i, j+2]、...[i, n-1]也都是子数组
	可以把[i,j]看作是一个滑动窗口，当满足条件时，ans+=n-j;
	然后i右移一格，如果还是，则继续累加。所以内循环i右移，使区间不满足，外循环j右移使区间满足

	总结
		右界右移，使区间能满足条件
		左界右移，使区间不满足条件

		满足条件的区间的左界 与其右界之后的每个右界都能构成完全子数组
*/

int countCompleteSubarrays(vector<int>& nums) {
	// 统计数组里不同元素的个数
	unordered_map<int, int> map;
	for (auto el : nums)
	{
		map[el]++;
	}
	const int n = map.size();
	map.clear();

	int ans = 0;
	int l = 0;
	int r = 0;
	int count = 0;
	while (r < nums.size())
	{
		map[nums[r]]++;
		if (1 == map[nums[r]])
		{
			++count;
			
			while (l <= r && count >= n)
			{
				ans += nums.size() - r;
				map[nums[l]]--;
				if (0 == map[nums[l]])
				{
					--count;
				}
				++l;
			}
		}
		++r;
	}

	return ans;
}