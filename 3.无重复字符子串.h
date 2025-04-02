#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

/*
	�Ӵ���������
	��������
	���������ַ�������ѳ��֣���ǰ�˳��ַ���ֱ��û���ظ���
	�����ظ��ַ����ж�ͨ���ַ�����bool��ӳ��ʵ�֣����ڴ���д��Сд��ĸ��������char[26]
	���ڶ������͵��ַ�����unordered_map<char, int>
*/

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.empty())
		{
			return 0;
		}

		int res = 0;
		unordered_map<char, int> map;
		for (int i = 0, j = 0;j < s.length();++j)
		{
			while (0 < map[s[j]])
			{
				map[s[i++]]--;
			}

			++map[s[j]];
			res = std::max(res, j - i + 1);
		}

		return res;

	}
};