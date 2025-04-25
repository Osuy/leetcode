#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	���Ϊk��������ĸ���

	����Ԫ�ؿ���Ϊ�������Բ����û�������
	ע�⵽�������ʵ������ǰ׺����������Կ�����ǰ׺��
	����presum[j]��ֻ��Ҫ֪��ǰ׺��Ϊ presum[j]- k ���ֹ� ���μ�������
	��ϣ��ż�ֵ��Ϊǰ׺�͡����ִ���
*/

int subarraySum(vector<int>& nums, int k) {
	int ans = 0;
	unordered_map<int, int> map;
	// û���κ�Ԫ��ʱ������Ϊ 0������1��
	map[0] = 1;
	int presum = 0;
	for (int i = 0;i < nums.size();++i)
	{
		presum += nums[i];
		if (map.contains(presum - k))// presum  ��Ҫ���� presum-k������У��� �����ִ����ۼӵ�����
		{
			ans += map[presum - k];
		}
		map[presum]++;
	}

	return ans;
}