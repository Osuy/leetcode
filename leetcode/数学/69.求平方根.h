#pragma once
#include "../base_header.h"
/*
	难度：考查二分法

	由于取值范围是[0, INT_MAX]
	所以答案的范围是[0, 49340]，需要注意的区间需要包括0

*/

int mySqrt(int x) {
	int l = 0, r = min(x, 46340) + 1; // 前闭后开区间
	while (l < r)
	{
		long long mid = l + (r - l) / 2; // mid使用long long 防止溢出
		if (mid * mid > x)
		{
			r = mid;
		}
		else if ((mid + 1) * (mid + 1) <= x)
		{
			l = mid + 1;
		}
		else
		{
			return mid;
		}
	}

	return r;
}