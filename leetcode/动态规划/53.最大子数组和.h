#pragma once
#include "../base_header.h"
/*
	难度：中等
	求一个数组中的最大子数组的和，元素可以为负


	若dp[i]表示数组[0...i]的最大子数组和，则dp[i+1]依然无法推导
	因为dp[i]所代表的那个子数组，不一定和el[i+1]相邻
	所以，修改dp的定义，dp[i]表示以el[i]结尾的最大子数组和
	那么答案并不是dp.back()而是dp数组的最大元素，不过在求dp时，就可以用一个额外的变量取最大值

	再者，由于dp[i+1]只依赖于dp[i]所以可以把dp数组优化为变量
*/
namespace q53_152
{
int maxSubArray(vector<int>& nums) {

	int dp = 0;
	int ans = nums[0];
	for (int i = 0; i < nums.size(); ++i)
	{
		dp = max(dp + nums[i], nums[i]);
		ans = max(ans, dp);
	}

	return ans;
}
}