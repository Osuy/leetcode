#pragma once
#include "../base_header.h"
/*
	难度：中等
	求和为k的子数组的个数

	由于元素可以为负，所以不能用滑动窗口
	注意到区间和其实是两个前缀和相减，所以可以用前缀和
	对于presum[j]，只需要知道前缀和为 presum[j]- k 出现过 几次即可于是
	哈希存放键值对为前缀和、出现次数
*/

int subarraySum(vector<int>& nums, int k) {
	int ans = 0;
	unordered_map<int, int> map;
	// 没有任何元素时，即和为 0，出现1次
	map[0] = 1;
	int presum = 0;
	for (int i = 0;i < nums.size();++i)
	{
		presum += nums[i];
		if (map.contains(presum - k))// presum  需要的是 presum-k，如果有，则 将出现次数累加到答案上
		{
			ans += map[presum - k];
		}
		map[presum]++;
	}

	return ans;
}