#pragma once
#include "../base_header.h"
/*
	�Ѷȣ�����
	ɾ���ַ����е�����ʹ�ַ�����Ϊ��Ч���ʽ 
	��������ɾ��������С���ַ���

	��ΪҪ��ɾ��������С�Ķ������ɵ����飬�����뵽������ȱ���
	����ɾ��ÿһ���ַ����õ�N���µ��ַ�����Ȼ����֤�Ƿ������Ч�ģ����ޣ�������һ��
	��N���ַ�������ɾ��ÿ���ַ����õ�N*(N-1)�����ַ����ٴ���֤

	�����֤���ο�20����Ч���ţ���
		���������ַ�������'('��')'������ַ�����Ϊ���ǲ�Ӱ����ʽ����Ч��
		��¼'('��')'�ĸ��� ��
		�������')'�ĸ�������'('ʱ��˵����ǰ�ı��ʽ��Ч�������������ʽ��Ч
		��������ʱ�����'('�ĸ�������')'��Ҳ˵�����ʽ��Ч

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