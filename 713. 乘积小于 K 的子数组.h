#pragma once
#include <vector>
using std::vector;

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
		int res = 0;
		int i = 0, j = 0;
		int mul = 1;
		for (;j < nums.size();++j)
		{
			mul *= nums[j];
			while (k <= mul && i <= j)
			{
				mul /= nums[i++];
			}

			res += j - i + 1;
		}

		return res;
	}
};