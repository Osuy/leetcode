#pragma once
#include "../base_header.h"
/*
	难度：困难
	删除字符串中的括号使字符串成为有效表达式 
	返回所有删除次数最小的字符串

	因为要求删除次数最小的多个答案组成的数组，容易想到广度优先遍历
	挨个删除每一个字符，得到N个新的字符串，然后验证是否存在有效的，若无，进入下一层
	对N个字符串挨个删除每个字符，得到N*(N-1)个新字符，再次验证

	如何验证（参考20题有效括号）：
		遍历所有字符，无视'('和')'以外的字符，因为它们不影响表达式的有效性
		记录'('和')'的个数 差
		如果出现')'的个数大于'('时，说明此前的表达式无效，于是整个表达式无效
		遍历结束时，如果'('的个数大于')'，也说明表达式无效

*/

vector<string> removeInvalidParentheses(string s) {
	auto is_valid = [](const string& str)
		{
			int n = 0;
			for (auto c : str)
			{
				if ('(' == c)n++;
				else if (')' == c)n--;

				if (n < 0)return false;
			}
			return n == 0;
		};

	queue<string> q;
	q.push(s);
	vector<string> ans;
	unordered_set<string> found;
	found.insert(s);
	while (!q.empty())
	{
		int size = q.size();
		bool stop = false;
		for (int i = 0;i < size;++i)
		{
			string str = q.front();
			q.pop();
			if (is_valid(str))
			{
				ans.push_back(str);
				stop = true;
			}
			else if (!stop)
			{
				for (int j = 0; j < str.length(); ++j)
				{
					if (str[j] != '(' && str[j] != ')')continue;
					string tmp = str;
					tmp.erase(j, 1);
					if (!found.contains(tmp))
					{
						q.push(tmp);
						found.insert(tmp);
					}
				}
			}
		}

		if (stop)break;
	}
	string str;
	return ans;
}