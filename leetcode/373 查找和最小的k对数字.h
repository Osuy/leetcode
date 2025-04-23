#pragma once
#include "base_header.h"
/*
	�Ѷȣ��е�
	���ͣ���ά���� ÿ�к�ÿ�ж��Ƿǵݼ��ģ���ǰk��Ԫ��
	��Ŀ����������nums1��nums2������(nums1[i], nums2[j])��һ��Ԫ������nums1����һ������nums2
		��ǰK������


	���԰��������Կ���һ����������nums1��nums2���Ƿǵݼ��ģ����Ծ����ÿ�к�ÿ�ж��Ƿǵݼ���
	ÿ�����Ե��±ߺ��ұߵ�Ԫ��һ������
	������ǰkС��Ԫ�ء���������KС��Ԫ�����Ƶ��ⲻһ�������Է���ҲҲ��һ����
	���KС��Ԫ�أ������öѣ�Ҳ�����ö��ֲ��ҡ�
	��������Ҫ������ǰKС��Ԫ�أ�����ֻ���ö�
	(0,0)��Ȼ����С�ģ��ڶ�С����(0,1)��(1��0)��Ȼ��ȷ������һ���ǵڶ�С�ĺ󣬵���С���� ����һ�� �� �ڶ�С���±ߺ��ұߣ� ����֮����С��
	��ÿ�ζ�Ҫ��һЩԪ����ѡ����С�ģ���Ϊ��iС�ģ�Ȼ���ڰ������±ߺ��ұ߼��뵽������ٴӼ�����ѡ��i+1С��
	��Ҫ(i, j-1)���ұ� ��(i-1,j)���±߶���(i,j)��Ҳ���ǻ��ظ���ӣ������Ҫȥ��
*/

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k)
{
	vector<vector<int>>ans;
	struct num_pair
	{
		int i1 = 0;
		int i2 = 0;
		int sum = 0;
		bool operator<(const num_pair& other)const 
		{
			return sum < other.sum;
		}
	};
	priority_queue<num_pair, vector<num_pair>, std::greater<num_pair>> q;
	unordered_set<long long> used;

	while (ans.size() < k)
	{
		auto p = q.top();
		q.pop();
		ans.emplace_back(nums1[p.i1], nums2[p.i2]);
		auto key = ((long long)(p.i1 + 1) << 32) + p.i2;
		if (!used.contains(key))
		{
			used.insert(key);
			q.emplace(p.i1 + 1, p.i2, nums1[p.i1 + 1] + nums2[p.i2]);
		}

		key = ((long long)p.i1 << 32) + p.i2 + 1;
		if (!used.contains(key))
		{
			used.insert(key);
			q.emplace(p.i1, p.i2 + 1, nums1[p.i1] + nums2[p.i2 + 1]);
		}
	}

	return ans;
}