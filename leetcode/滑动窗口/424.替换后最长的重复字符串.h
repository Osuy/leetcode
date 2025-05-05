#pragma once
#include "../base_header.h"

/*
	�Ѷȣ��е�


	�ؼ���Ҫ��ʶ����������Ҫ���ڵ�ǰ������ظ��ַ���������
	ֻ��Ҫֱ���������ֹ�������ظ���������
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