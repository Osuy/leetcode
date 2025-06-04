#pragma once
#include "../base_header.h"
/*
	难度：中等
	此题像53题那样不能使用动态规划。因为动态规划会舍弃负数乘积，但是两个负数相乘能得到正数
	可以考虑使用前缀和的变体，前缀乘积

	前缀积为正时，总是直接和ans取最大值，因为正数自然除以任何大于1的数都会变小，所以不除（或理解为除以1，preProduct[0]）
	前缀积为负时，需要除以最大的负数前缀积，因为负数除以一个负数会得到正数，为了尽可能大，需要被除数负数尽可能大
	用一个变量维护前缀乘积，另一个变量维护最小负数前缀积（初始为1）

	注意前缀积需要考虑元素为0的问题，遇到0后续所有前缀积都为0
	处理办法是跳过0，并重新开始计算前缀积
*/

int maxProduct(vector<int>& nums) {
	int minn = 1;// 最小负数前缀积，初始为0
	int preproduct = 1;// 前缀积
	int ans = INT_MIN;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (0 == nums[i]) // 遇到0，跳过，并重置变量
		{
			minn = 1;
			preproduct = 1;
			ans = max(ans, 0);// 由于存在0，所以答案至少为0
			continue;
		}

		preproduct *= nums[i];
		if (preproduct < 0)
		{
			ans = max(ans, preproduct / minn);
			minn = minn < 0 ? max(minn, preproduct) : preproduct;
		}
		else
		{
			ans = max(ans, preproduct);
		}
	}

	return ans;
}