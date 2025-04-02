#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

/*
	子串是连续的
	滑动窗口
	连续载入字符，如果已出现，则前端出字符，直至没有重复。
	有无重复字符的判断通过字符表与bool的映射实现，对于纯大写或纯小写字母，可以用char[26]
	对于多种类型的字符，用unordered_map<char, int>
*/

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.empty())
		{
			return 0;
		}

		int res = 0;
		unordered_map<char, int> map;
		for (int i = 0, j = 0;j < s.length();++j)
		{
			while (0 < map[s[j]])
			{
				map[s[i++]]--;
			}

			++map[s[j]];
			res = std::max(res, j - i + 1);
		}

		return res;

	}
};