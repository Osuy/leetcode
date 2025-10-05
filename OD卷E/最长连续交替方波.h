#pragma once
#include <string>
#include <iostream>
/*
	一个方波型号是由0和1组成的，其中不存在连续的0，但存在连续的1
	连续交替方波指0101010波
	如果存在连续的1，则不是
	找到信号中的最长连续交替方波
*/
namespace q1
{ 
std::string longestOZWave(std::string_view str)
{
	std::string ans{};
	auto l = 0, r = 0;
	bool correct = true;
	while (r < str.length())
	{
		r++;
		// 遇到了两个连续的0，信号结束，求长度
		if ('0' == str[r - 1] && (r == str.length() || '0' == str[r]))
		{
			if (correct && r - l > ans.length())
			{
				ans = str.substr(l, r - l);
			}

			l = r;
			correct = true;
		}
		else if('1' == str[l])// 信号的起点错误，直接区间归零
		{
			l = r;
			correct = true;
		}
		else
		{
			if ('1' == str[r - 1] && (r == str.length() || '1' == str[r]))
			{
				correct = false;
			}
		}
	}

	return ans;
}

void test()
{
	std::cout << longestOZWave("00101010101100001010010") << std::endl;
}
}