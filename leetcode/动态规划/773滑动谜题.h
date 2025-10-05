#pragma once
#include "base_header.h"

/*
	难度：困难
	在2行3列的拼图里随机摆放012345 六个数字
	只移动0和它相邻的数字互换，最终拼出123 450
	求最少步数

	分析：
		相当于是求0移动的最少步数，首先想到bfs，并且是带层数的
		考虑队列元素，需要知道数组的状态，和i的位置，如果数组的状态已经拼过则跳过
		数组的状态可以用一个字符串来实现，然后用hash表保存字符来实现存放所有出现过的状态
		0与相邻数字互换可以转化为字符串的两个字符互换
*/

int slidingPuzzle(std::vector<std::vector<int>>& board) {
	std::string target = "123450";
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
constexpr int near_offset[4] = { 1,-1,3,-3 };
int slidingPuzzle2(vector<vector<int>>& board) {
	const string target = "123450";
	string str;
	int zero_i = 0;
	int n = 0;
	unordered_set<string> used;
	for (auto& vec : board)
	{
		for (auto el : vec)
		{
			if (0 == el)
			{
				zero_i = n;
			}
			++n;
			str.push_back(el + '0');
		}
	}
	used.insert(str);
	queue<pair<const string, int>> q;
	q.emplace(str, zero_i);
	int step = 0;
	while (!q.empty())
	{
		auto size = q.size();
		for (auto k = 0; k < size; ++k)
		{
			const auto cstr = q.front().first;
			auto cindex = q.front().second;
			q.pop();

			if (cstr == target)
			{
				return step;
			}

			for (int i = 0; i < 4; ++i)
			{
				if (cindex == 2 && near_offset[i] == 1)continue;
				if (cindex == 3 && near_offset[i] == -1)continue;
				int index = cindex + near_offset[i];
				if (index < 0 || index >5)continue;
				str = cstr;
				swap(str[cindex], str[index]);
				if (used.contains(str))continue;
				used.insert(str);
				q.emplace(str, index);
			}
		}
		//324
		//150

		++step;
	}

	return -1;
}

void test773()
{
	vector<vector<int>> board{ {3, 2, 4}, {1,5,0} };
	slidingPuzzle(board);
	slidingPuzzle2(board);
}