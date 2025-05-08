#pragma once
#include "../base_header.h"

/*
	�Ѷȣ�����
	һ����СΪk�Ļ������ڴ�����ͷ����������β��ÿ�λ���һ���󻬶��ڼ䴰���ڵ��������ֵ

	ֻ���ϵ���ܳ�Ϊ���������Ԫ�ص�Ԫ�ء�
	���磺iĿǰ�Ǵ��ڵ����Ԫ�أ���ôi��ǰ��Ԫ��������ζ������Ϊδ�������Ԫ�أ���Ϊ��i����֮ǰ�������Ѿ���������
	j�Ǵ����ڵ�i֮������Ԫ�أ���ôi~j֮���Ԫ��Ҳ�����Ϊδ�������Ԫ��
	ֻ��i��j���Լ�j�Ժ��δ���ڶ���Ԫ����Ҫ��ע�������Ƚ��ȳ����ص㣬���ҵ�����
	�����뵽�������У������һ�ʱ�Ҳ�Ԫ����ӣ��Ѷ�βС����Ԫ�صĳ��ӣ����ֶ��ڵ����ݼ�
	���Ԫ��������ӵ��Ƕ��ף�����
*/

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	deque<int> max_indics;
	int i = 0;
	// �Ƚ�k-1��Ԫ�����
	for (; i < k - 1;++i)
	{
		while (!max_indics.empty() && nums[max_indics.back()] < nums[i])
		{
			max_indics.pop_back();
		}
		max_indics.push_back(i);
	}

	vector<int> ans;
	for (;i < nums.size();++i)
	{
		// ÿ�����ά�ֶ��ڵ����ݼ�
		while (!max_indics.empty() && nums[max_indics.back()] < nums[i])
		{
			max_indics.pop_back();
		}

		max_indics.push_back(i);
		// �ѵ�ǰ������ָԪ�ش����
		ans.push_back(nums[max_indics.front()]);

		if (i - k + 1 == max_indics.front())
		{
			max_indics.pop_front();
		}
	}

	priority_queue<vector<int>> q;
	ans.rbegin().operator*();
	return ans;
}