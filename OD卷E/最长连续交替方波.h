#pragma once
#include <string>
#include <iostream>
/*
	һ�������ͺ�����0��1��ɵģ����в�����������0��������������1
	�������淽��ָ0101010��
	�������������1������
	�ҵ��ź��е���������淽��
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
		// ����������������0���źŽ������󳤶�
		if ('0' == str[r - 1] && (r == str.length() || '0' == str[r]))
		{
			if (correct && r - l > ans.length())
			{
				ans = str.substr(l, r - l);
			}

			l = r;
			correct = true;
		}
		else if('1' == str[l])// �źŵ�������ֱ���������
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