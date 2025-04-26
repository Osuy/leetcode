#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	����һ�������һ����x��ÿ�β�����������׻�βȡһ������x���ȥ
	�����ǡ�ü���0���򷵻����ٵĲ����������򷵻�-1

	������Ŀ�ķ�Χ��10^5���Բ���ʹ��˫ѭ���㷨��ͬʱ��Ϊ�����������Բ���ʹ�÷��η�
	��Ҫ����ʹ��˫ָ�롣����Ԫ�ض�Ϊ�������Կ��ǻ������ڣ����Ϊ�����򻬶�����ʧЧ����Ҫ��ǰ׺��+��ϣ��

	����˼����֪��Ŀ�ȼ��� ��Ϊsum-x���������
	�����ҽ縺���ۼӣ���縺����٣�����С��sum-x�ҽ����ƣ�������sum-xʱ���������
	Ȼ���ж��Ƿ�ǡ�� = sum-x������ǣ��������еĴ𰸱Ƚϴ�С��ȡ�ϴ���
	���մ������鳤�� - ans
*/

int minOperations(vector<int>& nums, int x) {
	int sum = accumulate(nums.begin(), nums.end(), -x);

	int l = 0, r = 0;
	int ans = -1;
	while (r < nums.size())
	{
		sum -= nums[r];
		r++;
		while (sum < 0 && l < r)
		{
			sum += nums[l++];
		}

		if (0 == sum)
		{
			ans = max(ans, r - l);
		}
	}
	return ans < 0 ? -1 : nums.size() - ans;
}

/*
	���ڱ�ÿ�β���ֻ���ܴ��׻�βȡһ��Ԫ�أ�����������������ԡ��Ҵ����������˼���
	ֻ����ȡԪ�ء�ֻ��βȡԪ�ء������������ն�����һ���ڶ���֮�䣬���ǿ���
	��һ�����˽���ת������һ�����ˣ�����¼�м������Ĵ�
*/

int minOperations2(vector<int>& nums, int x) {
	// ��ȫ��ȡ�׶�
	int sum = 0;
	int l = 0;
	while (l < nums.size() && sum < x)
	{
		sum += nums[l++];
	}

	if (sum < x && l == nums.size())return -1;

	int ans = sum == x ? l : INT_MAX;

	// ÿ���˳�һ������������һ��Ԫ�أ����sum<x������һ�������Ԫ��
	int r = nums.size();
	while (l > 0)
	{
		sum -= nums[--l];
		while (sum < x)
		{
			sum += nums[--r];
		}

		if (sum == x)
		{
			ans = min(ans, l + (int)nums.size() - r);
		}
	}
	return INT_MAX == ans ? -1 : ans;
}