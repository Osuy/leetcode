#pragma once

#include <string>
using std::string;

/*
	拆解为 一个字符和一个字符串相乘 以及 一组字符串累加 两个问题
	
*/
class Solution 
{
public:

	string multiply(string num1, char num2)
	{
		string res(num1.length() + 1, '0');

		int k = 0;
		for (int i = 0; i < num1.length(); ++i)
		{
			int mul = k + (num1[num1.length() - 1 - i] - '0') * (num2 - '0');
			res[res.length() - 1 - i] = (mul % 10) + '0';
			k = mul / 10;
		}

		if (k)
		{
			res[0] = k + '0';
		}

		return res;
	}

	string multiply(string num1, string num2)
	{
		string res(num1.length() + num2.length(), '0');

		for (int i = 0; i < num1.length(); ++i)
		{
			auto tmp = multiply(num2, num1[num1.length() - 1 - i]);
			if (i > 0)
			{
				tmp += string(i, '0');
			}

			int k = 0;
			for (int j = 0;j< tmp.length();++j)
			{
				int n = k + res[res.length() - 1 - j] - '0' + tmp[tmp.length() - 1 - j] - '0';
				k = n / 10;
				res[res.length() - 1 - j] = (n % 10) + '0';
			}

			if (0 != k)
			{
				res[res.length() - tmp.length()] = k + '0';
			}
		}

		while (res[0] == '0')
		{
			res = res.substr(1);
		}

		return res;
	}

};