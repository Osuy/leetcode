#pragma once
#include "../base_header.h"
/*
	对于字符串s和字典
	如果字符串s可以插入空格形参一个句子，句子里的所有单词都出现在字典里
	返回所有句子

	显然回溯法
	对于对于剩余字符串rest，初始时为s
	取前i个字符组成字串，如果出现在字典里，则插入一个空格，然后rest = 空格后的字符串
	继续递归

	和单词拆分1一样有两种方法判断前缀
*/

vector<string> wordBreak(string s, vector<string>& wordDict) {
	vector<string> ans;
	string str;
	str.reserve(s.size() * 2);
	unordered_set<string_view> dict(wordDict.begin(), wordDict.end());
	auto dfs = [&](this auto&& dfs, string_view rest)
		{
			if (rest.empty())
			{
				ans.push_back(str);
				return;
			}

			if (!str.empty())
			{
				str.push_back(' ');
			}
			auto size = str.size();

			for (int i = 1; i <= rest.size(); ++i)
			{
				if (!dict.contains(string_view{ rest.begin(), rest.begin() + i }))
				{
					continue;
				}

				str.append(rest.begin(), rest.begin() + i);
				dfs(string_view{ rest.begin() + i, rest.end() });
				str.resize(size);
			}

			// 方法2
			for (int i = 0; i < wordDict.size(); ++i)
			{
				if (!rest.starts_with(wordDict[i]))continue;

				str.append(wordDict[i]);
				dfs(string_view{ rest.begin() + wordDict[i].size(), rest.end() });
				str.resize(size);
			}

			if (!str.empty() && str.back() == ' ')
			{
				str.pop_back();
			}
		};

	dfs(s);
	return ans;
}