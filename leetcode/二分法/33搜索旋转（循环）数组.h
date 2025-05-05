#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	�Ǹ���һ�����飬����һ���ϸ��������ԭ��ƽ�����ⵥλ�������
	��[0,k)��[k, n)���ǵ����ģ���el[0]>el[n-1]
	��������Ѱ��target��Ҫ��ʱ�临�Ӷ�O(logn)


	˼·������һ����ת�������飬��Ȼ���Կ��Ƕ��ַ���������Ҫ��ָ������
	���Ĺ۵��Ǿ����ܵذ��������䴦���꣬���ڶ��µ����䣬������һ��ѭ����mid�����з�
	������81�⡣����������ظ�Ԫ�أ�����ȷ��midǰ���������ҽ�ȥ��
*/

int search(vector<int>& nums, int target) {
	int l = 0, r = nums.size();
	while (l < r)
	{
		//���Ԫ�ؿ��ظ������ҽ���ȥ���ڼ���mid
		while (l + 1 < r && nums[l] == nums[l + 1])++l;
		while (l < r - 2 && nums[r - 1] == nums[r - 2])--r;

		int mid = (l + r) / 2;
		// ���targetС��mid
		// 1.mid���������䣨���С���ҽ磩�������������mid+1
		// 2.[l, mid)�������£���������targetһ���������У��������������mid+1�����½����´�ѭ���и�
		// 3.[mid,r)����������targetС���ҽ磬��target�����У��������������mid+1
		// 4.[mid,r)����������target�����ҽ磬��target��[l,���µ�)�У��ҽ�������mid�����½����´�ѭ���и�
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