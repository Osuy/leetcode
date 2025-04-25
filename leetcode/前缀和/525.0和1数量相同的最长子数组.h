#pragma once
#include "../base_header.h"

/*
	难度：中等
	一个数组只有0和1，求0和1数量相等的子数组的最大长度

	0和1数量相等，并不关心数值本身，题目可以改成1和2数量相等
	因此为了方便计算使用前缀和计算，可以把0当作-1，题目变为：子数组和为0的最大长度

	对于k = presum[j]，如果存在i<j，k = presum[i]
	那么 0 = presum[j] - presum[i]，即[i-1, j]区间内的元素和为0
	因此无需往前遍历寻找和为0的左界，而是记录每一个 和，索引 的键值对
	当存入的见不存在，直接存入
	当存入的键已存在时，就找到了一个子数组，求差得到长度。并且不更新索引，使索引总是保持最小
	还需map[0] = -1，因为[0,j]的和为0时，没有对应的左界，所以需要以-1为左界
*/

int findMaxLength(vector<int>& nums) {
	unordered_map<int, int> map;
	map[0] = -1;
	int presum = 0;
	int ans = 0;
	for (int i = 0;i < nums.size();++i)
	{
		presum += (nums[i] ? 1 : -1);
		if (map.contains(presum))
		{
			ans = max(ans, i - map[presum]);
		}
		else
		{
			map[presum] = i;
		}
	}
	return ans;
}