#pragma once
#include "base_header.h"
/*
	难度中等
	矩阵每行每列都按非递减排序，求第k小的元素

	方法一：直接排序
	方法二：堆排序+去重
		初始将左上角入堆，然后循环出堆，将其右边和下边的元素入堆，可能存在重复，所以要用哈希表去重
		出堆k次得到答案
		外循环k次，堆排序的swim要小于 logk次，所以总时间复杂度O小于(klogk)

	方法三：二分查找
		既然存在非递减排序，要联想到二分查找。第k小的元素一定在矩阵的左上角
		但这是一个不规则的左上角。可以通过小于某值来取一个左上角，如果能取到一半的元素，效率高
		因此该值可以用mid (min + max)/2来得到。
		当左上角的元素数量小于k，说明mid小于答案，于是mid = (mid+right)/2在次计算左上角的数量
		直到左上角恰好为k，此时right 即为答案

		统计左上角元素个数的方法复杂度是o(max(row, col))，二分查找的确认mid时间复杂度是O(log(row*col))
		所以总复杂度为O(max(row, col) * log(row*col))，并不比堆排序更快，但作为一种二维二分查找的思路可以记忆
*/

int kthSmallest(vector<vector<int>>& matrix, int k)
{
	// 计算小于N的元素的数量
	auto count_smaller_than_or_equal_N = [&matrix](int N)
	{
		int i = matrix.size() - 1;
		int j = 0;
		int count = 0;
		// 从左下角开始，如果<=N则该点以上的都<=N，累加到count，去下一列
		// 否则向上
		while (j < matrix[0].size() && i >= 0)
		{
			if (matrix[i][j] <= N)
			{
				count += i + 1;
				++j;
			}
			else
			{
				--i;
			}
		}

		return count;
	};

	int left = matrix[0][0];
	int right = matrix.back().back();
	while (left < right)
	{
		int mid = (left + right) >> 1;
		int count = count_smaller_than_or_equal_N(mid);
		if (count < k)
		{
			left = mid + 1;
		}
		else
		{
			right = mid;
		}
	}

	return right;
}