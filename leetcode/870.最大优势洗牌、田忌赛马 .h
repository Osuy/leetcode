#pragma once
#include "base_header.h"
/*
	难度：中等
	给出两个数组nums1和nums2
	请将nums1重新排列，使nums1相同下标的元素尽可能多地大于nums2。返回排列好的数组

	假如两个数组都有序，那么从大到小遍历nums2，如果nums1的可选元素里的最大元素能够大于nums2剩余最大元素
	则两个元素对位。如果不能，则从nums1可选元素里取最小的对位

	对nums1排序
	由于答案依赖nums2的顺序，所以不能对nums2排序需要一个额外的有序数组记录nums2的元素以及对应下标
*/

vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
	// 存放元素值和对应下表，<运算使用元素值比较
	struct wv
	{
		int w = 0;
		int v = 0;
		bool operator<(const wv& other)const
		{
			return w < other.w;
		}
	};

	// 大顶堆存放nums2的元素和下表
	priority_queue<wv, vector<wv>> queue;
	for (int i = 0;i < nums2.size();++i)
	{
		queue.push({ nums2[i],i });
	}

	// 排序nums1
	vector<int> ans(nums1.size());
	sort(nums1.begin(), nums1.end());

	// 维护nums1的剩余区间
	// 如果当前队首元素值大于区间右侧，说明无法有优势，则将区间左侧（最小）元素放到对应位置上
	// 否则说明存在优势将区间右侧（最大）元素放到对应位置
	// 更新区间
	int mini = 0, maxi = nums1.size() - 1;
	while (!queue.empty())
	{
		auto wvel = queue.top();
		queue.pop();
		if (wvel.w < nums1[maxi])
		{
			ans[wvel.v] = nums1[maxi--];
		}
		else
		{

			ans[wvel.v] = nums1[mini++];
		}
	}
	
	return ans;
}