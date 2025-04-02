#pragma once
#include <string>
#include <span>
#include <format>
using std::string;
using std::string_view;
using std::span;
using std::vector;

/*
	难度：中等
	
	类型：双指针、二分查找

	题目：
		给你两个字符串 s 和 p ，其中 p 是 s 的一个 子序列 。同时，给你一个元素 互不相同 且下标 从 0 开始 计数的整数数组 removable ，该数组是 s 中下标的一个子集（s 的下标也 从 0 开始 计数）。
		请你找出一个整数 k（0 <= k <= removable.length），选出 removable 中的 前 k 个下标，然后从 s 中移除这些下标对应的 k 个字符。
		整数 k 需满足：在执行完上述步骤后， p 仍然是 s 的一个 子序列 。
		更正式的解释是，对于每个 0 <= i < k ，先标记出位于 s[removable[i]] 的字符，接着移除所有标记过的字符，然后检查 p 是否仍然是 s 的一个子序列。

	分析：
		用一个函数判断是否是子序列
		removable是需要移出的字母的下标，但是不做真正的移初，因为会重新创建字符串，消耗性能，所以用mask来遮盖s

		如果字符串和removable都很大，会超出时间限制。由于始终是移除前k个字母，所以可以用二分查找优化
*/

class Solution {
public:
	// p是否是s的子序列，使用双指针方法，提供一个mask，来遮盖s里的元素
	bool is_sub_sequence(string_view s, string_view p, span<char> mask)const
	{
		if (s.length() < p.length())
		{
			return false;
		}

		int i = 0, j = 0;
		while (i < p.length())
		{
			while (j < s.length() && (s[j] != p[i] || mask[j]))++j;// 如果j被mask遮盖了，也继续

			if (j >= s.length())return false;

			++i;
			++j;
		}

		return  true;
	}

	int maximumRemovals(string s, string p, const vector<int>& removable)
	{
		vector<char> mask{};
		mask.resize(s.length());
		int l = 0;
		int r = removable.size();
		int i = (l + r) >> 1;
		for (int j = 0;j < i;++j)
		{
			mask[removable[j]] = 1;
		}

		while (l < r)
		{
			if (is_sub_sequence(s, p, mask))
			{
				l = i;
				i = (1 + i + r) >> 1;
				for (int j = l;j < i;++j)
				{
					mask[removable[j]] = 1;
				}
			}
			else
			{
				r = i - 1;
				i = (i + l) >> 1;
				for (int j = i;j <= r;++j)
				{
					mask[removable[j]] = 0;
				}
			}
		}
		return i;
	}
};
