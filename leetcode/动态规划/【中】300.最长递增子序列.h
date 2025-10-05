#pragma once
#include "../base_header.h"
/*
	�������������У��������ϸ����

	���� dp[i] Ϊ����ǰi��Ԫ�صĴ�
	��ô��������dp[0...i-1]�Ƶ�������

	�����п��԰���nums[i]��Ҳ���Բ�����
	�����������dp[i]��ֵӦ���� 1 + ��һ��nums[j]<nums[i]����nums[j]��β��������
	�������������dp[i] = dp[i-1]

	Ȼ����dp[j]���ܴ�����nums[j]��β�������У� ���Ǵ���nums[j]��β��������
	����dp[i]������dp[i-1]��dp[j]����õ�

	�Ϻõ������޸�dp�ĺ��壺��nums[i]��β��������
	��������dp�����Ԫ��
*/

int lengthOfLIS(vector<int>& nums) {
	auto size = nums.size();
	vector<int>dp(size, 1);

	for (int i = 1; i < size; ++i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			if (nums[j] < nums[i])
			{
				dp[i] = max(dp[i], 1 + dp[j]);
			}
		}
	}

	return *std::max_element(dp.begin(), dp.end());
}