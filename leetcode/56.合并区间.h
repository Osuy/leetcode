#pragma once
#include "base_header.h"

/*
	难度中等

	由于给出了区间，所以可以很容易得到diff数组
	对diff数组进行求前 n项和可以得到

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
	网友的神级写法
*/

class Solution2 {
public:

	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{
		// 找到最大的曲线右侧
		int maxindex = 0;
		for (const auto& el : intervals)
		{
			maxindex = std::max(maxindex, el[1]);
		}

		// 创建一个数组当作数轴，其能容纳最右侧的两倍（目的是把题目的[]闭区间转换成[)前闭后开区间
		// 可以有效规避单点区间：[x, x] => [x, x+ 1) ）
		// 对于每个一区间，它的起点在数轴上自增，终点在数轴上自减
		// 于是沿着数轴累加每个值时，如果进入了区间，则和为正
		// 如果离开的区间，则和为负。额外用一个state变量记录进入的区间的七点
		// 则 区间为 state/2, i/2
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