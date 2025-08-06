#pragma once
#include "../base_header.h"
/*
	求数组中第K大的元素
	通常采用小顶堆，遍历数组push堆，使堆容量保持K，超过则pop
	最后堆顶是第K大的元素
	时间复杂度O(Nlogk)，会超时

	考虑使用快速排序，因为快速排序的每一层递归，都是求出了某个元素的位置
	然后以该元素为中点将当前数组一分为二，继续递归

	先把问题转化为求第N-K小的元素
	如果某一次确定了某元素的位置是P，若P<N-K，则只递归右边
	否则，只递归左边
	每次递归遍历的数组元素在理想情况下是上一次的一半
	所以总时间复杂度是： N + N/2 + N/4 + ... + 1 = 2N = O(N)
*/

int findKthLargest(vector<int>& nums, int k) 
{
	k = nums.size() - k;
	auto p = partition(nums);
	while (p != k)
	{
		if (p < k)
		{
			p = partition(span<int>{ nums.begin() + p + 1, nums.end() });
		}
		else
		{
			p = partition(span<int>{ nums.begin(), nums.begin() + p });
		}
	}

	return nums[k];
}

int partition(span<int> nums)
{
	auto pivot = nums.back();

	int i = 0, j = 0;
	while (j < nums.size() - 1)
	{
		if (nums[j] < pivot)
		{
			swap(nums[i++], nums[j]);
		}
		++j;
	}

	swap(nums[i], nums[j]);
	
	return i;
}