#pragma once
#include "../base_header.h"
/*
	求数组的最长子序列，且满足严格递增

	假设 dp[i] 为数组前i个元素的答案
	那么它可以由dp[0...i-1]推导出来吗？

	子序列可以包含nums[i]，也可以不包含
	如果包含，则dp[i]的值应该是 1 + 第一个nums[j]<nums[i]且以nums[j]结尾的子序列
	如果不包含，则dp[i] = dp[i-1]

	然而，dp[j]不能代表以nums[j]结尾的子序列， 而是代表nums[j]结尾的子序列
	所以dp[i]不能由dp[i-1]或dp[j]计算得到

	较好的做法修改dp的含义：以nums[i]结尾的子序列
	而答案则是dp的最大元素
*/

int lengthOfLIS(vector<int>& nums) {
	auto size = nums.size();
	vector<int>dp(size, 1);

	for (int i = 1; i < size; ++i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			if (nums[j] < nums[i])
			{
				dp[i] = max(dp[i], 1 + dp[j]);
			}
		}
	}

	return *std::max_element(dp.begin(), dp.end());
}