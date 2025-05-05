#pragma once
#include "../base_header.h"
/*
	难度：中等
	那给出一个数组，它是一个严格递增数组原地平移任意单位后的数组
	即[0,k)和[k, n)都是单调的，且el[0]>el[n-1]
	从数组中寻找target，要求时间复杂度O(logn)


	思路：对于一个旋转递增数组，仍然可以考虑二分法，但是需要拆分更多情况
	核心观点是尽可能地把有序区间处理完，对于断崖的区间，交给下一次循环让mid继续切分
	变体如81题。如果数组有重复元素，则在确定mid前，先让左右界去重
*/

int search(vector<int>& nums, int target) {
	int l = 0, r = nums.size();
	while (l < r)
	{
		//如果元素可重复，左右界先去重在计算mid
		while (l + 1 < r && nums[l] == nums[l + 1])++l;
		while (l < r - 2 && nums[r - 1] == nums[r - 2])--r;

		int mid = (l + r) / 2;
		// 如果target小于mid
		// 1.mid在有序区间（左界小于右界），则左界收缩至mid+1
		// 2.[l, mid)不含断崖，即单调，target一定不在其中，所以左界收缩至mid+1，断崖交给下次循环切割
		// 3.[mid,r)不含断崖且target小于右界，则target在其中，所以左界收缩至mid+1
		// 4.[mid,r)不含断崖且target大于右界，则target在[l,断崖点)中，右界收缩至mid，断崖交给下次循环切割
		if (nums[mid] < target)
		{
			if (nums[l] < nums[r - 1])
			{
				if (nums[r - 1] < target)return -1;
				l = mid + 1;
			}
			else
			{
				if (nums[l] < nums[mid])
				{
					l = mid + 1;
				}
				else
				{
					if (target <= nums[r - 1])
					{
						l = mid + 1;
					}
					else
					{
						r = mid;
					}
				}
			}
		}
		else if (nums[mid] > target)
		{
			if (nums[l] < nums[r - 1])
			{
				if (target < nums[l])return -1;
				r = mid;
			}
			else
			{
				if (nums[l] > nums[mid])
				{
					r = mid;
				}
				else
				{
					if (target < nums[l])
					{
						l = mid + 1;
					}
					else
					{
						r = mid;
					}
				}
			}
		}
		else
		{
			return mid;
		}
	}

	return -1;
}