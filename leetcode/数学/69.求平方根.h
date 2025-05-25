#pragma once
#include "../base_header.h"
/*
	�Ѷȣ�������ַ�

	����ȡֵ��Χ��[0, INT_MAX]
	���Դ𰸵ķ�Χ��[0, 49340]����Ҫע���������Ҫ����0

*/

int mySqrt(int x) {
	int l = 0, r = min(x, 46340) + 1; // ǰ�պ�����
	while (l < r)
	{
		long long mid = l + (r - l) / 2; // midʹ��long long ��ֹ���
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