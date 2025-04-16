#pragma once
#include "base_header.h"

/*
	难度：中等
	类型：二分查找
	题目：
		给你一个浮点数 hour ，表示你到达办公室可用的总通勤时间。要到达办公室，你必须按给定次序乘坐 n 趟列车。另给你一个长度为 n 的整数数组 dist ，其中 dist[i] 表示第 i 趟列车的行驶距离（单位是千米）。
		每趟列车均只能在整点发车，所以你可能需要在两趟列车之间等待一段时间。
		例如，第 1 趟列车需要 1.5 小时，那你必须再等待 0.5 小时，搭乘在第 2 小时发车的第 2 趟列车。
		返回能满足你在时限前到达办公室所要求全部列车的 最小正整数 时速（单位：千米每小时），如果无法准时到达，则返回 -1 。

		生成的测试用例保证答案不超过 107 ，且 hour 的 小数点后最多存在两位数字。
*/

class Solution
{
public:
	// dist 基于 speed 的花费时间
	double use_time(span<int> dists, int speed)const
	{
		double res = 0.0;
		for (int i = 0;i < dists.size() - 1;++i)
		{
			res += ceil((double)dists[i] / speed);
		}

		return res + ceil((double)dists.back() / speed);
	}
	
	int minSpeedOnTime(span<int> dists, double hour)
	{
		if (ceil(hour) < dists.size())
		{
			return -1;
		}

		// 二分查找法，基于题目输出要求设定最大、最小边界
		// 如果其平均值满足，则尝试更小的值
		// 如果其平均值不满足，则尝试更大的值
		// 知道左右边界重合（因为是整数，所以差1也要退出循环）
		int l = 1;
		int r = 1e7 + 1;
		while (l < r)
		{
			double ut = use_time(dists, (l + r) >> 1);
			if (ut < hour)
			{
				r = (l + r) >> 1;
			}
			else
			{
				l = 1 + ((l + r) >> 1);
			}
		}
	}
};