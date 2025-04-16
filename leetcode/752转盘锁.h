#pragma once
#include "base_header.h"

/*
	难度中等
	从0000开始转动转盘得到target，可以向上或向下转，求最小转动次数
	而且不允许转出deadends里的数字

	分析：
		转盘转出已出现的数字也不行，所以可以用一个hashset存放deadends以及已转出过的数字
		每次转动可以对四个数字分布上下转动共8种，但不能转到已转出过的数字和deadends里的数字
		下一次转动在上一次转动的结果上继续
		求最少转动次数，容易联想到使用bfs，队列元素直接存放转盘数字的字符串即可

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