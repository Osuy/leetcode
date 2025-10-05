#pragma once
#include "../base_header.h"
/*
	难度：中等
	求一个数组中的最大子数组的和，元素可以为负

	右界不断移动，累计和。尽管遇到了负数
	但是负数后面可能还有正数，使和更大，所以保留
	一旦和为负数，则就移动左界使数组重新为正
	不过因为和已经为负了，说明遇到了负数足以大于之前的和，
	因此左界最终会移到有界，也就是子数组为空，和为0
	相当于子数组重新开始累加。所以左界可以直接省略

	元素的取值范围是[-10000, 10000]所以答案的下限是-10001
*/
namespace q53_152
{
	int maxSubArray(vector<int>& nums) {
		int ans = -10001;
		int sum = 0;
		int i = 0;
		while (i < nums.size())
		{
			sum += nums[i++];
			ans = max(ans, sum);
			if (sum < 0)
			{
				sum = 0;
			}
		}
		return ans;
	}
}