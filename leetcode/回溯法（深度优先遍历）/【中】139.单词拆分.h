#pragma once
#include "../base_header.h"
/*
	给出一个字符串和一个字典
	求字符串能否由字典里的单词拼出

	两种思路：
		1.遍历字典，如果当前字符串由单词i作为前缀，则减去单词i，递归
		2.遍历剩余字符串的前i个字符，如果前i个字母构成的字符串存在于字典中，则减去，递归

	第1种空间复杂度更低，
	第2种方式利用hash表加速，时间复杂度更低
	实际比较，如果不剪枝，二者都会超时；剪枝后第1种更快，推测是直接在s上比较前缀，命中率会比hash表更好

	关于减去前缀，实际上可以使用string_view 无需真正发生字符串的修改

	关于超时，字典里的单词可能非常刁钻。
	例如 a和aaaaa
	如果字符串都能匹配，当五此递归a或一次aaaaa后，剩余的字符串是一样的，就会产生重复计算
	可以使用备忘录进行剪枝
*/


bool wordBreak(string s, vector<string>& wordDict) {
	// s和dict的内容都不会被修改，可以使用string_view而不担心悬垂
	unordered_set<string_view> dict(wordDict.begin(), wordDict.end());
	unordered_map<string_view, bool>visited;
	auto dfs = [&](this auto&& dfs, string_view current) -> bool 
		{
			if (current.empty())
			{
				return true;
			}

			if (visited.contains(current))
			{
				return visited[current];
			}

			auto ret = false;
			for (int i = 1; i <= current.size(); ++i) 
			{
				if (!dict.contains(string_view{ current.begin(), current.begin() + i }))
				{
					continue;
				}

				if (dfs(string_view{ current.begin() + i, current.end() }))
				{
					ret = true;
					break;
				}
			}

			visited[current] = ret;
			return ret;
		};

	return dfs(s);
}