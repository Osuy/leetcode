#pragma once
#include "leetcode/base_header.h"
/*
	һ�������������ļ���

	��Ŀ��[i,j]�����䣬ֱ��ȥ��������������˫ѭ������֤�����Ƿ�������ĿҪ�����ҲҪһ��ѭ����
	���Դ������ⷨʱ�临�Ӷ���O(n^3)���������������������Ŀ��������10e5�����ģ�Ҳ���Ǳ���Ҫ�Ż���O(nlogn)����
	��������[i,j]����������ͨ��[0,i-1]��[0,j]��������õ�����������������档������ȶ�
		[0,i-1]��[0,j]���������㣬Ȼ����������������������õ����

	����������[i,j]��Ԫ�صĺͣ������֪[0,i-1]��[0,j]�ڵĺͣ�������������ɵõ���

	��������
		һ��������
		�����������
		������ͨ�����������������õ���

	ǰ׺�;�����Ҫ��Ϲ�ϣ���¼�Ѿ�������ǰ׺��������������������
*/

/*
	ǰ׺�ͱ���	
*/
int longestWPI(vector<int>& hours) {
	//��ǰ׺�ͣ����ȼ�һ����0Ҳ������
	vector<int> presum(hours.size() + 1, 0);
	for (int i = 0;i < hours.size();++i)
	{
		presum[i + 1] = (hours[i] > 8 ? 1 : -1) + presum[i];
	}

	int ans = 0;
	unordered_map<int, int>map;
	for (int i = 0;i < presum.size();++i)
	{
		if (!map.contains(presum[i]))
		{
			map[presum[i]] = i;
		}

		if (presum[i] > 0)
		{
			ans = max(ans, i);
		}
		else if (map.contains(presum[i] - 1))
		{
			ans = max(ans, i - map[presum[i] - 1]);
		}
	}

	return ans;
}