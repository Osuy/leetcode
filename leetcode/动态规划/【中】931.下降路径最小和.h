#pragma once
#include "../base_header.h"
/*
	给出一个n*n的矩阵
	求从矩阵第一行到最后一行的路径的最小和
	路径上的方格必须有共同的顶点
	p(i,j)的可选的下一个路径节点个(i+1, j-1)/(i+1, j)/(i+1, j+1)三个
	

	首先可以联想到三叉树，求数的最小高度和
	由于会经过重复的节点，所以可以用备忘录
	这是自顶向下的解法

	自底向上，使用dp数组，推导状态转移方程
	对于到达点i,j所经过的路径最短值，必然是到达(i-1, j-1)/(i-1, j)/(i-1, j+1)的路径和的最小值，再加上i,j点的值

*/

int minFallingPathSum(vector<vector<int>>& matrix) {
	auto n = matrix.size();
	vector<vector<int>> dp(n, vector<int>(n, 10000));

	dp[0] = matrix[0];

	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			auto minv = dp[i - 1][j];
			if (j > 0)
			{
				minv = min(minv, dp[i - 1][j - 1]);
			}
			if (j < n - 1)
			{
				minv = min(minv, dp[i - 1][j + 1]);
			}

			dp[i][j] = matrix[i][j] + minv;
		}
	}

	return *min_element(dp.back().begin(), dp.back().end());

	// 备忘录解法
	unordered_map<int, int> saved;
	auto n = matrix.size();

	auto dfs = [&](this auto&& dfs, int i, int j)
		{
			if (j < 0 || j >= n)
			{
				return 10000;
			}

			if (i >= n)return 0;

			auto index = i * n + j;
			if (saved.contains(index))
			{
				return saved[index];
			}

			auto ret = matrix[i][j] + min(min(dfs(i + 1, j), dfs(i + 1, j + 1)), dfs(i + 1, j - 1));
			saved[index] = ret;
			return ret;
		};

	int ans = 10000;
	for (int i = 0; i < n; ++i)
	{
		ans = min(ans, dfs(0, i));
	}

	return ans;
}