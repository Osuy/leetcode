#pragma once
#include "../base_header.h"

/*
	难度：中等


	关键是要意识到，并无需要窗口当前的最大重复字符及其数量
	只需要直到曾经出现过的最大重复次数即可
*/

int characterReplacement(string s, int k) {
	vector<int> counts(26, 0);
	int maxn = 0;
	int len = s.length();
	int l = 0, r = 0;
	while (r < len)
	{
		maxn = max(maxn, ++counts[s[r++] - 'A']);
		if (r - l - maxn > k)
		{
			--counts[s[l++] - 'A'];
		}
	}

	return r - l;
}