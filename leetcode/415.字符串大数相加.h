#pragma once
#include "base_header.h"

class Solution {
public:
	string addStrings(string num1, string num2) {
		int common = std::min(num1.length(), num2.length());
		string res(1 + std::max(num1.length(), num2.length()), '0');
		int k = 0;
		for (int i = 1;i <= common; ++i)
		{
			int n = k + num1[num1.length() - i] - '0' + num2[num2.length() - i] - '0';
			k = n / 10;
			res[res.length() - i] = '0' + (n % 10);
		}

		if (num1.length() < num2.length())
		{
			for (int i = num1.length();i < num2.length(); ++i)
			{
				int n = k + num2[num2.length() - i - 1] - '0';
				k = n / 10;
				res[num2.length() - i] = '0' + (n % 10);
			}
		}
		else
		{
			for (int i = num2.length();i < num1.length(); ++i)
			{
				int n = k + num1[num1.length() - i - 1] - '0';
				k = n / 10;
				res[num1.length() - i] = '0' + (n % 10);
			}
		}

		if (k)
		{
			res[0] = '0' + k;
		}
		else
		{
			res = res.substr(1);
		}

		return res;
	}
};