#pragma once
#include "base_header.h"
/*
	难度：中等
	题型：二维矩阵， 每行和每列都是非递减的，求前k个元素
	题目：两个数组nums1和nums2，数对(nums1[i], nums2[j])，一个元素来自nums1，另一个来自nums2
		求前K个数对


	可以把所有数对看出一个矩阵，由于nums1和nums2都是非递减的，所以矩阵的每行和每列都是非递减的
	每个数对的下边和右边的元素一定更大
	求矩阵的前k小的元素。这题和求第K小的元素相似但解不一样，所以方法也也不一样。
	求第K小的元素，可以用堆，也可以用二分查找。
	但是这题要求所有前K小的元素，所以只能用堆
	(0,0)必然是最小的，第二小的是(0,1)或(1，0)，然后确认其中一个是第二小的后，第三小的是 （另一个 或 第二小的下边和右边） 三者之中最小的
	即每次都要从一些元素中选出最小的，作为第i小的，然后在把它的下边和右边加入到集合里，再从集合里选第i+1小的
	主要(i, j-1)的右边 和(i-1,j)的下边都是(i,j)，也就是会重复入队，因此需要去重
*/

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k)
{
	vector<vector<int>>ans;
	struct num_pair
	{
		int i1 = 0;
		int i2 = 0;
		int sum = 0;
		bool operator<(const num_pair& other)const 
		{
			return sum < other.sum;
		}
	};
	priority_queue<num_pair, vector<num_pair>, std::greater<num_pair>> q;
	unordered_set<long long> used;

	while (ans.size() < k)
	{
		auto p = q.top();
		q.pop();
		ans.emplace_back(nums1[p.i1], nums2[p.i2]);
		auto key = ((long long)(p.i1 + 1) << 32) + p.i2;
		if (!used.contains(key))
		{
			used.insert(key);
			q.emplace(p.i1 + 1, p.i2, nums1[p.i1 + 1] + nums2[p.i2]);
		}

		key = ((long long)p.i1 << 32) + p.i2 + 1;
		if (!used.contains(key))
		{
			used.insert(key);
			q.emplace(p.i1, p.i2 + 1, nums1[p.i1] + nums2[p.i2 + 1]);
		}
	}

	return ans;
}