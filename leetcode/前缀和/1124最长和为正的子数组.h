#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	�������������飬�Ҹ��������ڴ���8��Ԫ�ر�С�ڵ���8��Ԫ�ظ���

	˼·������Ҫע�⵽ֻ���ϵԪ���Ƿ����8�����ع�ϵԪ�ر����ֵ
	���Կ��԰�Ԫ�ؿ�����1������8����-1��С�ڵ���8��Ȼ�������������飬��������ĺʹ���0
	��ô���䡢��ͣ�Ԫ�ؿ���Ϊ�������������뵽��ǰ׺��+��ϣ��
	�ʹ���0����ζ��presum[i] > presum[j]
	����presum[0] = 0���Զ��������presum[i]>0ʱ��[0, i]��������
	presum[i]<=0ʱ��ҪȥѰ����Զ��j��ע��������Զ�Ķ�������С�ģ����Բ���ѭ��ȥ��
	��Ϊÿ��Ԫ���ۼӵ�ǰ׺���϶�ֻ��1��-1������������� presum[i]
	��[0,i-1]�ķ�Χ��һ������j�� presum[j] = presum[i]-1���������ն���
	����ֻ��Ҫȥ�� presum[i]-1 �Ƿ���ڼ��ɣ�ͨ����ǰ������presum��ŵ���ϣ���ɿ����ж�
*/

int longestWPI(vector<int>& hours) {
	vector<int> presum(hours.size() + 1, 0);
	for (int i = 0;i < hours.size();++i)
	{
		presum[i + 1] = (hours[i] > 8 ? 1 : -1) + presum[i];
	}

	int ans = 0;
	unordered_map<int, int> map;
	for (int i = 0;i < presum.size();++i)
	{
		if (!map.contains(presum[i]))
		{
			map[presum[i]] = i;
		}
		// ������������Ϊ0��Ӧ��������Ӹ�else����
		// ���Ǳ������������ʹ���0��Ҫ��map[presum[i]-1]�������if���޹ص�
		// ����д��ͬһ����������

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
/*
	�ⷨ��������ջ
	ע�⵽����i��Ҫȥ����Զ��j����presum[i] > presum[j]
	����0��ʼ�ң����������Լ�������������С���Լ��ľ�����Զ�ġ�
	��˿���ά��һ�������ݼ���ջ��
	ע�����i���ұߴ���k��presum[k] > presum[i]
	��ô[j,k]����һ�����㣬�ұ�[j,i]��������˲��ܴ������ұ���i����Ҫ�������

*/
int longestWPI2(vector<int>& hours) {
	vector<int> presum(hours.size() + 1, 0);
	vector<int> st;
	st.push_back(0);
	for (int i = 0; i < hours.size(); ++i)
	{
		presum[i + 1] = (hours[i] > 8 ? 1 : -1) + presum[i];
		if (presum[i + 1] < presum[st.back()])
		{
			st.push_back(i+1);
		}
	}

	int ans = 0;
	for (int i = presum.size()-1;i>=0;--i)
	{
		while (!st.empty() && presum[i] > presum[st.back()])
		{
			ans = max(ans, i - st.back());
			st.pop_back();
		}
	}

	return ans;
}