#pragma once
#include "../base_header.h"
/*
	�������е�K���Ԫ��
	ͨ������С���ѣ���������push�ѣ�ʹ����������K��������pop
	���Ѷ��ǵ�K���Ԫ��
	ʱ�临�Ӷ�O(Nlogk)���ᳬʱ

	����ʹ�ÿ���������Ϊ���������ÿһ��ݹ飬���������ĳ��Ԫ�ص�λ��
	Ȼ���Ը�Ԫ��Ϊ�е㽫��ǰ����һ��Ϊ���������ݹ�

	�Ȱ�����ת��Ϊ���N-KС��Ԫ��
	���ĳһ��ȷ����ĳԪ�ص�λ����P����P<N-K����ֻ�ݹ��ұ�
	����ֻ�ݹ����
	ÿ�εݹ����������Ԫ�����������������һ�ε�һ��
	������ʱ�临�Ӷ��ǣ� N + N/2 + N/4 + ... + 1 = 2N = O(N)
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