#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <vector>

/*
	1 2
	2
	32
	324
	5324

*/

void q1()
{
	std::deque<int> q;
	int n = 0;
	std::cin >> n;

	int operator_count = 0;
	bool unsorted = false;
	for (int i = 0; i < n; ++i)
	{
		std::string command;
		std::cin >> command;
		if (command.starts_with("head add "))
		{
			auto number = command.substr(10, command.length() - 10);
			auto num = stoi(number);
			if (!q.empty() && num != q.front() - 1)
			{
				unsorted = true;
			}
			q.push_front(num);
		}
		else if (command.starts_with("tail add "))
		{
			auto number = command.substr(10, command.length() - 10);
			q.push_back(stoi(number));
		}
		else
		{
			if (unsorted)
			{
				unsorted = false;
				std::sort(q.begin(), q.end());
			}
			q.pop_front();
		}
	}
}

void q2()
{
	int n = 0, d = 0;
	std::cin >> n >> d;
	std::vector<int> vec(n, 0);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> vec[i];
	}

	int k = 0;
	int k2 = 0;
	int score = -1;
	int diff_sum = 0;
	std::vector<bool>used(n, false);
	auto dfs = [&](this auto&& dfs)
		{
			for (int i = 0; i < n; ++i)
			{
				if (used[i])continue;
				used[i] = true;
				for (int j = 0; j < n; ++j)
				{
					if (used[j])continue;
					auto diff = abs(vec[i] - vec[j]);

					used[j] = true; 
					if (diff <= d)
					{
						k += 2;
						k2++;
						diff_sum += diff
					}

					dfs();

					used[j] = false;
					if (diff <= d)
					{
						k -= 2;
						k2--;
						diff_sum -= diff
					}
				}

				used[i] = false;
			}
		};
}