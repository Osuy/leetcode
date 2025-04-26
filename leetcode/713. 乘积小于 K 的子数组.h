#pragma once
#include "base_header.h"

/*
	�Ѷȣ��е�
	��������������Ԫ�س˻�Сk������

	�������룺���鳤��β10^4�������裬������˫ָ�롣��������Ԫ��Ϊ���������û�������
	���һ����[i, j)�ĳ˻�С��k��������������ĳ˻�ҲС��k������һ����j-i
	���ǻ��������ҽ�����˻������˻�����kʱ�����������С�˻����õ�ǡ�ó˻�С��k������[i,j)
	ans+=j-i
		
*/
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
	if (k == 0)return 0;
	int ans = 0;
	int mul = 1;
	int size = nums.size();
	int l = 0, r = 0;

	while (r < size)
	{
		mul *= nums[r++];
		while (mul >= k && l < r)
		{
			mul /= nums[l++];
		}
		ans += r - l;
	}

	return ans;
}