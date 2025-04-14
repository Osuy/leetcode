#pragma once
#include "base_header.h"

/*
	˫��ѭ���ⷨ���Խ��

	���Ҫ�û������ڣ���Ҫ��ʶ����ÿ���һ���һ�񣬴����ڵ�������������� j-i+1
	��Ϊ�����½��봰�ڵ�Ԫ�� el[j]�������ӵ��������У�
		1.el[j]
		2.el[j-1],el[j]
		...
		el[i],el[i+1]...el[j-1l,el[j]
		����Ϊ j-i+1
		
*/
class Solution {
public:
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
};