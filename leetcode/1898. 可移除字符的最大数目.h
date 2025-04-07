#pragma once
#include <string>
#include <span>
#include <format>
using std::string;
using std::string_view;
using std::span;
using std::vector;

/*
	�Ѷȣ��е�
	
	���ͣ�˫ָ�롢���ֲ���

	��Ŀ��
		���������ַ��� s �� p ������ p �� s ��һ�� ������ ��ͬʱ������һ��Ԫ�� ������ͬ ���±� �� 0 ��ʼ �������������� removable ���������� s ���±��һ���Ӽ���s ���±�Ҳ �� 0 ��ʼ ��������
		�����ҳ�һ������ k��0 <= k <= removable.length����ѡ�� removable �е� ǰ k ���±꣬Ȼ��� s ���Ƴ���Щ�±��Ӧ�� k ���ַ���
		���� k �����㣺��ִ������������� p ��Ȼ�� s ��һ�� ������ ��
		����ʽ�Ľ����ǣ�����ÿ�� 0 <= i < k ���ȱ�ǳ�λ�� s[removable[i]] ���ַ��������Ƴ����б�ǹ����ַ���Ȼ���� p �Ƿ���Ȼ�� s ��һ�������С�

	������
		��һ�������ж��Ƿ���������
		removable����Ҫ�Ƴ�����ĸ���±꣬���ǲ����������Ƴ�����Ϊ�����´����ַ������������ܣ�������mask���ڸ�s

		����ַ�����removable���ܴ󣬻ᳬ��ʱ�����ơ�����ʼ�����Ƴ�ǰk����ĸ�����Կ����ö��ֲ����Ż�
*/

class Solution {
public:
	// p�Ƿ���s�������У�ʹ��˫ָ�뷽�����ṩһ��mask�����ڸ�s���Ԫ��
	bool is_sub_sequence(string_view s, string_view p, span<char> mask)const
	{
		if (s.length() < p.length())
		{
			return false;
		}

		int i = 0, j = 0;
		while (i < p.length())
		{
			while (j < s.length() && (s[j] != p[i] || mask[j]))++j;// ���j��mask�ڸ��ˣ�Ҳ����

			if (j >= s.length())return false;

			++i;
			++j;
		}

		return  true;
	}

	int maximumRemovals(string s, string p, const vector<int>& removable)
	{
		vector<char> mask{};
		mask.resize(s.length());
		int l = 0;
		int r = removable.size();
		int i = (l + r) >> 1;
		for (int j = 0;j < i;++j)
		{
			mask[removable[j]] = 1;
		}

		while (l < r)
		{
			if (is_sub_sequence(s, p, mask))
			{
				l = i;
				i = (1 + i + r) >> 1;
				for (int j = l;j < i;++j)
				{
					mask[removable[j]] = 1;
				}
			}
			else
			{
				r = i - 1;
				i = (i + l) >> 1;
				for (int j = i;j <= r;++j)
				{
					mask[removable[j]] = 0;
				}
			}
		}
		return i;
	}
};
