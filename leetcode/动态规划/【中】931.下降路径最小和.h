#pragma once
#include "../base_header.h"
/*
	����һ��n*n�ľ���
	��Ӿ����һ�е����һ�е�·������С��
	·���ϵķ�������й�ͬ�Ķ���
	p(i,j)�Ŀ�ѡ����һ��·���ڵ��(i+1, j-1)/(i+1, j)/(i+1, j+1)����
	

	���ȿ������뵽����������������С�߶Ⱥ�
	���ڻᾭ���ظ��Ľڵ㣬���Կ����ñ���¼
	�����Զ����µĽⷨ

	�Ե����ϣ�ʹ��dp���飬�Ƶ�״̬ת�Ʒ���
	���ڵ����i,j��������·�����ֵ����Ȼ�ǵ���(i-1, j-1)/(i-1, j)/(i-1, j+1)��·���͵���Сֵ���ټ���i,j���ֵ

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

	// ����¼�ⷨ
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