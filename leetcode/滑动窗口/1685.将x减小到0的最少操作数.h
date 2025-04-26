#pragma once
#include "../base_header.h"
/*
	难度：中等
	给定一个数组和一个数x，每次操作从数组的首或尾取一个数从x里减去
	如果能恰好减到0，则返回最少的操作数；否则返回-1

	由于题目的范围是10^5所以不能使用双循环算法。同时因为数组无序，所以不好使用分治法
	需要考虑使用双指针。由于元素都为正，所以考虑滑动窗口（如果为负，则滑动窗口失效，需要用前缀和+哈希表）

	逆向思考可知题目等价于 和为sum-x的最长子数组
	于是右界负责累加，左界负责减少，当和小于sum-x右界右移，当大于sum-x时，左界右移
	然后判断是否恰好 = sum-x，如果是，则与已有的答案比较大小，取较大者
	最终答案是数组长度 - ans
*/

int minOperations(vector<int>& nums, int x) {
	int sum = accumulate(nums.begin(), nums.end(), -x);

	int l = 0, r = 0;
	int ans = -1;
	while (r < nums.size())
	{
		sum -= nums[r];
		r++;
		while (sum < 0 && l < r)
		{
			sum += nums[l++];
		}

		if (0 == sum)
		{
			ans = max(ans, r - l);
		}
	}
	return ans < 0 ? -1 : nums.size() - ans;
}

/*
	由于被每次操作只可能从首或尾取一个元素，操作结果具有连续性。且存在两个极端即：
	只从首取元素、只从尾取元素。根据拉格朗日定理，答案一定在二者之间，于是可以
	从一个极端渐渐转化到另一个极端，并记录中间遇到的答案
*/

int minOperations2(vector<int>& nums, int x) {
	// 先全部取首端
	int sum = 0;
	int l = 0;
	while (l < nums.size() && sum < x)
	{
		sum += nums[l++];
	}

	if (sum < x && l == nums.size())return -1;

	int ans = sum == x ? l : INT_MAX;

	// 每次退出一个首区间的最后一个元素，如果sum<x则增加一个区间的元素
	int r = nums.size();
	while (l > 0)
	{
		sum -= nums[--l];
		while (sum < x)
		{
			sum += nums[--r];
		}

		if (sum == x)
		{
			ans = min(ans, l + (int)nums.size() - r);
		}
	}
	return INT_MAX == ans ? -1 : ans;
}