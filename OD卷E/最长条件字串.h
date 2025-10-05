#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
/*
	寻找最长的子串，满足：
		1.每个字符出现不超过2次
		2.不包含某个字符
*/

namespace q4
{
int longestStr(std::string_view str, char C)
{
	auto l = 0, r = 0;
	std::unordered_map<char, int> freq;
	int above_2 = 0;
	int max_len = 0;
	while (r < str.length())
	{
		// 加入区间的字符计数+1，如果超过2，超2计数+1
		freq[str[r]]++;
		if (freq[str[r]] > 2)
		{
			above_2++;
		}
		r++;
		
		//缩小左界，如果有超过2的字符，或存在特殊字符，则收缩。由于是求最大长度，所以不用while
		if (above_2 || freq[C])
		{
			if (freq[str[l]] == 3)
			{
				above_2--;
			}
			freq[str[l]]--;
			
			l++;
		}

		max_len = std::max(max_len, r - l);
	}

	return max_len;
}

void test()
{
	std::cout << longestStr("ABC132", 'D');
	std::cout << longestStr("ABACA123D", 'D');
}
}