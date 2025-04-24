#pragma once
#include "leetcode/base_header.h"
/*
	一种用于求解区间的技巧

	题目求[i,j]的区间，直接去遍历所有区间是双循环，验证区间是否满足题目要求可能也要一次循环，
	所以纯暴力解法时间复杂度是O(n^3)，而对于输入是数组的题目基本都是10e5量级的，也就是必须要优化的O(nlogn)以下
	假如区间[i,j]的条件可以通过[0,i-1]和[0,j]进行运算得到，并且这种运算可逆。则可以先对
		[0,i-1]和[0,j]进行逆运算，然后再用两个区间正向运算得到结果

	例如求区间[i,j]内元素的和，如果已知[0,i-1]和[0,j]内的和，将两者相减即可得到答案

	三个特征
		一、求区间
		二、运算可逆
		三、可通过两个区间的逆运算得到答案

	前缀和经常需要配合哈希表记录已经遇到的前缀的索引或次数来加速求解
*/

/*
	前缀和变体	
*/
int longestWPI(vector<int>& hours) {
	//求前缀和，长度加一，让0也能运算
	vector<int> presum(hours.size() + 1, 0);
	for (int i = 0;i < hours.size();++i)
	{
		presum[i + 1] = (hours[i] > 8 ? 1 : -1) + presum[i];
	}

	int ans = 0;
	unordered_map<int, int>map;
	for (int i = 0;i < presum.size();++i)
	{
		if (!map.contains(presum[i]))
		{
			map[presum[i]] = i;
		}

		if (presum[i] > 0)
		{
			ans = max(ans, i);
		}
		else if (map.contains(presum[i] - 1))
		{
			ans = max(ans, i - map[presum[i] - 1]);
		}
	}

	return ans;
}