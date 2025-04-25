#pragma once
#include "../base_header.h"

/*
	�Ѷȣ��е�
	һ������ֻ��0��1����0��1������ȵ����������󳤶�

	0��1������ȣ�����������ֵ������Ŀ���Ըĳ�1��2�������
	���Ϊ�˷������ʹ��ǰ׺�ͼ��㣬���԰�0����-1����Ŀ��Ϊ���������Ϊ0����󳤶�

	����k = presum[j]���������i<j��k = presum[i]
	��ô 0 = presum[j] - presum[i]����[i-1, j]�����ڵ�Ԫ�غ�Ϊ0
	���������ǰ����Ѱ�Һ�Ϊ0����磬���Ǽ�¼ÿһ�� �ͣ����� �ļ�ֵ��
	������ļ������ڣ�ֱ�Ӵ���
	������ļ��Ѵ���ʱ�����ҵ���һ�������飬���õ����ȡ����Ҳ�����������ʹ�������Ǳ�����С
	����map[0] = -1����Ϊ[0,j]�ĺ�Ϊ0ʱ��û�ж�Ӧ����磬������Ҫ��-1Ϊ���
*/

int findMaxLength(vector<int>& nums) {
	unordered_map<int, int> map;
	map[0] = -1;
	int presum = 0;
	int ans = 0;
	for (int i = 0;i < nums.size();++i)
	{
		presum += (nums[i] ? 1 : -1);
		if (map.contains(presum))
		{
			ans = max(ans, i - map[presum]);
		}
		else
		{
			map[presum] = i;
		}
	}
	return ans;
}