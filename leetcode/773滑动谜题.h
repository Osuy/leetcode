#pragma once
#include "base_header.h"

/*
	�Ѷȣ�����
	��2��3�е�ƴͼ������ڷ�012345 ��������
	ֻ�ƶ�0�������ڵ����ֻ���������ƴ��123 450
	�����ٲ���

	������
		�൱������0�ƶ������ٲ����������뵽bfs�������Ǵ�������
		���Ƕ���Ԫ�أ���Ҫ֪�������״̬����i��λ�ã���������״̬�Ѿ�ƴ��������
		�����״̬������һ���ַ�����ʵ�֣�Ȼ����hash�����ַ���ʵ�ִ�����г��ֹ���״̬
		0���������ֻ�������ת��Ϊ�ַ����������ַ�����
*/

int slidingPuzzle(std::vector<std::vector<int>>& board) {
	std::string target = "123450";
	std::priority_queue < int, std::vector<int>, std::greater<int>> q;
	q.top();
	std::string origin;
	int i_index = 0;
	for (auto& el : board)
	{
		for (auto n : el)
		{
			if (n == 0) i_index = origin.length();
			origin.push_back(n + '0');
		}
	}
	std::unordered_set<std::string> set;
	struct qel_t
	{
		std::string str;
		int i = 0;
	};
	static int i_near[6][3] =
	{
		{1, 3, -1},
		{0, 2,  4},
		{1, 5, -1},
		{0, 4, -1},
		{1, 3,  5},
		{2, 4, -1},
	};
	std::queue<qel_t>  q;
	q.push({ origin, i_index });
	int step = 0;
	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0; i < size; ++i)
		{
			auto qel = q.front();
			q.pop();
			if (qel.str == target)return step;

			for (int i = 0; i < 3; ++i)
			{
				if (i_near[qel.i][i] < 0) continue;
				std::string str2 = qel.str;
				std::swap(str2[qel.i], str2[i_near[qel.i][i]]);
				if (set.contains(str2)) continue;

				set.insert(str2);
				q.push({ str2, i_near[qel.i][i] });
			}
		}
		step++;
	}

	return -1;
}