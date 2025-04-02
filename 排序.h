#pragma once
#include <vector>
using std::vector;

void qsort(vector<int>& nums, int l, int r)
{
	// 区间长度仅为1或边界无效，返回
	if (r - l < 2)return;

	// 定位到front和back
	int f = l, b = r - 1;
	int key = nums[(f + b)/2];
	nums[(f + b) / 2] = nums[f];
	while (f < b)
	{
		while (f < b&& key <= nums[b])--b;
		nums[f] = nums[b];
		while (f < b && nums[f] <= key)++f;
		nums[b] = nums[f];
	}

	nums[f] = key;

	qsort(nums, l, f);
	qsort(nums, f + 1, r);
}

void qsort(vector<int>& nums)
{
	qsort(nums, 0, nums.size());
}