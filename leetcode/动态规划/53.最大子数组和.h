#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	��һ�������е����������ĺͣ�Ԫ�ؿ���Ϊ��


	��dp[i]��ʾ����[0...i]�����������ͣ���dp[i+1]��Ȼ�޷��Ƶ�
	��Ϊdp[i]��������Ǹ������飬��һ����el[i+1]����
	���ԣ��޸�dp�Ķ��壬dp[i]��ʾ��el[i]��β������������
	��ô�𰸲�����dp.back()����dp��������Ԫ�أ���������dpʱ���Ϳ�����һ������ı���ȡ���ֵ

	���ߣ�����dp[i+1]ֻ������dp[i]���Կ��԰�dp�����Ż�Ϊ����
*/
namespace q53_152
{
int maxSubArray(vector<int>& nums) {

	int dp = 0;
	int ans = nums[0];
	for (int i = 0; i < nums.size(); ++i)
	{
		dp = max(dp + nums[i], nums[i]);
		ans = max(ans, dp);
	}

	return ans;
}
}