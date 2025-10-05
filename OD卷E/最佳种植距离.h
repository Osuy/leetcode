#pragma once
#include <vector>
#include <algorithm>
/*
	�������飬�����������������
	ȡn������������ʹ���������������

	������ֲ�����ǣ���������Ԫ��min����СԪ��max��[min, max]
	����������n����������������������������ֵ������ (max-min1)/n
	����ֲ����С����Ϊ1��
	�����ڴ������϶��ַ������ܹ�����ļ��

	�ж�һ�����D�Ƿ��ܹ����㣺
		��0������ҵ���һ���������D�����꣬count++����Ϊ�ϴ�����
		ѭ���ظ������������count>=n��˵�����D��������������ֲN����
*/


int maxInterval(const std::vector<int>& pos, int n)
{
	auto pos2 = pos;
	std::sort(pos2.begin(), pos2.end());
	auto could_apply = [&](int interval)->bool
		{
			auto last_pos = 0;
			auto count = 0;
			for (int i = 1; i < pos2.size(); ++i)
			{
				if (pos2[i] - pos2[last_pos] >= interval)
				{
					++count;
					last_pos = i;
				}
			}
			return count >= n;
		};
	int l = 1, r = pos2.back() - pos2.front() + 1;
	int ret = 1;
	while (l < r)
	{
		int mid = (l + r) / 2;
		if (could_apply(mid))
		{
			ret = mid;
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}

	return ret;
}
