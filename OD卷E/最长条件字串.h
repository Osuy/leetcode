#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
/*
	Ѱ������Ӵ������㣺
		1.ÿ���ַ����ֲ�����2��
		2.������ĳ���ַ�
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
		// ����������ַ�����+1���������2����2����+1
		freq[str[r]]++;
		if (freq[str[r]] > 2)
		{
			above_2++;
		}
		r++;
		
		//��С��磬����г���2���ַ�������������ַ���������������������󳤶ȣ����Բ���while
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