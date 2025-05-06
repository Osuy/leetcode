#pragma once
#include "base_header.h"
/*
	�Ѷȣ��е�
	������������nums1��nums2
	�뽫nums1�������У�ʹnums1��ͬ�±��Ԫ�ؾ����ܶ�ش���nums2���������кõ�����

	�����������鶼������ô�Ӵ�С����nums2�����nums1�Ŀ�ѡԪ��������Ԫ���ܹ�����nums2ʣ�����Ԫ��
	������Ԫ�ض�λ��������ܣ����nums1��ѡԪ����ȡ��С�Ķ�λ

	��nums1����
	���ڴ�����nums2��˳�����Բ��ܶ�nums2������Ҫһ����������������¼nums2��Ԫ���Լ���Ӧ�±�
*/

vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
	// ���Ԫ��ֵ�Ͷ�Ӧ�±�<����ʹ��Ԫ��ֵ�Ƚ�
	struct wv
	{
		int w = 0;
		int v = 0;
		bool operator<(const wv& other)const
		{
			return w < other.w;
		}
	};

	// �󶥶Ѵ��nums2��Ԫ�غ��±�
	priority_queue<wv, vector<wv>> queue;
	for (int i = 0;i < nums2.size();++i)
	{
		queue.push({ nums2[i],i });
	}

	// ����nums1
	vector<int> ans(nums1.size());
	sort(nums1.begin(), nums1.end());

	// ά��nums1��ʣ������
	// �����ǰ����Ԫ��ֵ���������Ҳ࣬˵���޷������ƣ���������ࣨ��С��Ԫ�طŵ���Ӧλ����
	// ����˵���������ƽ������Ҳࣨ���Ԫ�طŵ���Ӧλ��
	// ��������
	int mini = 0, maxi = nums1.size() - 1;
	while (!queue.empty())
	{
		auto wvel = queue.top();
		queue.pop();
		if (wvel.w < nums1[maxi])
		{
			ans[wvel.v] = nums1[maxi--];
		}
		else
		{

			ans[wvel.v] = nums1[mini++];
		}
	}
	
	return ans;
}