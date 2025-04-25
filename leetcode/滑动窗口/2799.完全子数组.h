#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	���һ������������������������е�Ԫ�أ����Ϊ��ȫ������
	���������ȫ������ĸ���

	����ĺ�������ͳ����ȫ������ĸ�����������Ҫ������е���������ȥ��֤�������Ƿ�Ϊ��ȫ������
	��Ϊ���һ��������[i, j]����ȫ�����飬��[i, j+1]��[i, j+2]��...[i, n-1]Ҳ����������
	���԰�[i,j]������һ���������ڣ�����������ʱ��ans+=n-j;
	Ȼ��i����һ��������ǣ�������ۼӡ�������ѭ��i���ƣ�ʹ���䲻���㣬��ѭ��j����ʹ��������

	�ܽ�
		�ҽ����ƣ�ʹ��������������
		������ƣ�ʹ���䲻��������

		������������������ �����ҽ�֮���ÿ���ҽ綼�ܹ�����ȫ������
*/

int countCompleteSubarrays(vector<int>& nums) {
	// ͳ�������ﲻͬԪ�صĸ���
	unordered_map<int, int> map;
	for (auto el : nums)
	{
		map[el]++;
	}
	const int n = map.size();
	map.clear();

	int ans = 0;
	int l = 0;
	int r = 0;
	int count = 0;
	while (r < nums.size())
	{
		map[nums[r]]++;
		if (1 == map[nums[r]])
		{
			++count;
			
			while (l <= r && count >= n)
			{
				ans += nums.size() - r;
				map[nums[l]]--;
				if (0 == map[nums[l]])
				{
					--count;
				}
				++l;
			}
		}
		++r;
	}

	return ans;
}