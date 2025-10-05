#pragma once
#include "../base_header.h"
/*
	�����ַ���s���ֵ�
	����ַ���s���Բ���ո��β�һ�����ӣ�����������е��ʶ��������ֵ���
	�������о���

	��Ȼ���ݷ�
	���ڶ���ʣ���ַ���rest����ʼʱΪs
	ȡǰi���ַ�����ִ�������������ֵ�������һ���ո�Ȼ��rest = �ո����ַ���
	�����ݹ�

	�͵��ʲ��1һ�������ַ����ж�ǰ׺
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

			// ����2
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