#pragma once
#include "../base_header.h"
/*
	在n*n棋盘里放置n个皇后，使她们互相不会攻击
	皇后的攻击范围是所在的行、列、斜线

	每层递归在该列上放置一个皇后。放置的可选列表是n，所以循环n次
	每次循环判断该行该列是否可放置

	直至全部皇后放置，求出一个答案
*/

vector<vector<string>> solveNQueens(int n) {

	vector<string> solution(n, string(n, '.'));// 初始化棋盘
	vector<vector<string>> ans;
	
	auto could_place = [&](int i, int j) -> bool // 判断(i, j)是否可放置
		{
			for (int k = 0; k < i; ++k)
			{
				if ('Q' == solution[k][j]
					|| ((j - (i - k)) >= 0 && 'Q' == solution[k][j - (i - k)])
					|| ((j + (i - k)) < n && 'Q' == solution[k][j + (i - k)]))
				{
					return false;
				}
			}

			return true;
		};

	auto dfs = [&](this auto&& dfs, int i)
		{
			if (i == n)// 达到n列，找到了一个解，存入ans
			{
				ans.push_back(solution);
				return;
			}

			auto& str = solution[i];
			for (int j = 0; j < n; ++j)
			{
				if (!could_place(i, j))continue;

				str[j] = 'Q'; // 放置皇后
				dfs(i + 1);
				str[j] = '.'; // 撤销放置
			}
		};

	dfs(0);

	// 迭代版
	// 由于迭代需要在函数自身的作用域内存放已做过的选择，所以需要一个额外的数组
	vector<int> indics(n, -1);
	int i = 0;
	while (i >= 0) // 如果i退回到了-1则找出了所有的答案，结束循环
	{
		if (n == i)
		{
			// 找到一个答案，回到上一层
			ans.push_back(solution);
			--i;
			continue;
		}

		if (indics[i] >= 0 && indics[i] < n)
		{
			solution[i][indics[i]] = '.';
		}

		do indics[i]++; while (!could_place(i, indics[i]) && indics[i] < n);

		if (indics[i] < n)
		{
			solution[i][indics[i]] = 'Q';
			
			++i;
		}
		else
		{
			// 回到上一层，重置这一层的皇后可选列表
			solution[i] = string(n, '.');
			indics[i] = -1;
			--i;
		}
	}

	return ans;
}