#pragma once
#include "../base_header.h"

/*
	难度：中等
	返回数组中任意一个严格大于相邻元素的元素的索引
	头尾元素只需计算它后/前一个相邻元素
	数组元素各不相等

	思路：对于任意一个元素num[i],如果num[i]<num[i+1]则说明i后面一定有峰
	反之，num[i]>num[i+1]则说明i前面一定有峰。于是可以用二分法缩小范围，最终求得峰值索引

	完全相同的代码，还可以解决 862寻找顶峰
*/

int findPeakElement(vector<int>& nums) {
	int size = nums.size();

	int l = 0, r = size - 1;

	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] > nums[mid + 1])
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}

	return l;
}