#pragma once
#include <vector>
#include <algorithm>
/*
	输入数组，代表可以种树的坐标
	取n个坐标种树，使它们两两距离最大

	树的种植区间是，数组的最大元素min和最小元素max，[min, max]
	在区间里种n棵树，且两两距离最大，则距离的最大值可以是 (max-min1)/n
	而种植的最小距离为1，
	可以在此区间上二分法查找能够满足的间距

	判断一个间距D是否能够满足：
		从0，向后找到第一个距离大于D的坐标，count++，设为上次坐标
		循环重复，结束后，如果count>=n。说明间距D可以在区间内种植N棵树
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
