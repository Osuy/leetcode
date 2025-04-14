#pragma once
#include "base_header.h"

/*
	�Ѷ��е�

	���ڸ��������䣬���Կ��Ժ����׵õ�diff����
	��diff���������ǰ n��Ϳ��Եõ�

*/

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{
		if (intervals.empty())return {};

		vector<vector<int>> res{};
		res.push_back(intervals.front());

		for (int i = 1;i < intervals.size();++i)
		{
			int j = res.size();
			for (int o = 0;o < j;++o)
			{
				if (overlap(res[o][0], res[o][1], intervals[i][0], intervals[i][1]))
				{
					res[o][0] = std::min(res[o][0], intervals[i][0]);
					res[o][1] = std::max(res[o][1], intervals[i][1]);
				}
				else
				{
					res.push_back(intervals[i]);
				}
			}
		}
		return res;


	}
};

/*
	���ѵ���д��
*/

class Solution2 {
public:

	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{
		// �ҵ����������Ҳ�
		int maxindex = 0;
		for (const auto& el : intervals)
		{
			maxindex = std::max(maxindex, el[1]);
		}

		// ����һ�����鵱�����ᣬ�����������Ҳ��������Ŀ���ǰ���Ŀ��[]������ת����[)ǰ�պ�����
		// ������Ч��ܵ������䣺[x, x] => [x, x+ 1) ��
		// ����ÿ��һ���䣬����������������������յ����������Լ�
		// �������������ۼ�ÿ��ֵʱ��������������䣬���Ϊ��
		// ����뿪�����䣬���Ϊ����������һ��state������¼�����������ߵ�
		// �� ����Ϊ state/2, i/2
		vector<int> arr(2 * maxindex + 2, 0);
		for (const auto& el : intervals)
		{
			arr[el[0] * 2]++;
			arr[el[1] * 2 + 1]--;
		}

		vector<vector<int>> ans;
		int state = -1;
		int cur = 0;
		for (int i = 0;i < arr.size();++i)
		{
			cur += arr[i];
			if (cur > 0)
			{
				if (-1 == state)
				{
					state = i;
				}
			}
			else
			{
				if (-1 != state)
				{
					ans.push_back({ state / 2, i / 2 });
					state = -1;
				}
			}
		}

		return ans;
	}
};