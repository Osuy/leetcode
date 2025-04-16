#pragma once
#include "base_header.h"

/*
	�Ѷ��е�
	��0000��ʼת��ת�̵õ�target���������ϻ�����ת������Сת������
	���Ҳ�����ת��deadends�������

	������
		ת��ת���ѳ��ֵ�����Ҳ���У����Կ�����һ��hashset���deadends�Լ���ת����������
		ÿ��ת�����Զ��ĸ����ֲַ�����ת����8�֣�������ת����ת���������ֺ�deadends�������
		��һ��ת������һ��ת���Ľ���ϼ���
		������ת���������������뵽ʹ��bfs������Ԫ��ֱ�Ӵ��ת�����ֵ��ַ�������

*/

int openLock(std::vector<std::string>& deadends, std::string target) {
	std::unordered_set<std::string> deadsets;

	for (auto& el : deadends)
	{
		deadsets.insert(el);
	}
	if (deadsets.contains("0000"))return -1;

	int step = 0;
	std::queue<std::string> q;
	q.push("0000");
	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0;i < size;i++)
		{
			auto qel = q.front();
			q.pop();
			if (qel == target)return step;
			for (int j = 0;j < 4;++j)
			{
				std::string str = qel;
				str[j] = '0' + (qel[j] - '0' + 1) % 10;
				if (!deadsets.contains(str))
				{
					deadsets.insert(str);
					q.push(str);
				}

				str[j] = '0' + (qel[j] - '0' + 9) % 10;
				if (!deadsets.contains(str))
				{
					deadsets.insert(str);
					q.push(str);
				}
			}
		}
		step++;
	}

	return -1;
}