#pragma once
#include "base_header.h"
/*
	�Ѷȣ��е�
	��һ���� '0' �� '1' ��ɵĶ�ά�����ڣ��ҵ�ֻ���� '1' ����������Σ������������

	������ijΪ���½ǵľ���
	�������ڵ���������α߳�side = max�� i-1 j �����ڵ���������Σ�i j-1 �����ڵ���������Σ�
	���matrix[i][j]Ϊ1������Կ���side+1�� ����ȥ����side+1�����ڵľ���Ԫ�أ����ȫΪ1����˵������side+1�߳��������Σ���������θ���

	��������
		�����ᵽ�ķ�����Ҫ����side + 1�����򣬺�ʱ�϶࣬�����޸�dp�������Ż�������Ҫ�������������Σ��߳���
		ԭ��dp[i][j]��¼�ľ�����������α߳������Ǳ��������֣����Զ�����һ������max_side����¼�����dp�Ϳ���ȥ�����������
		�Ż����dp����¼�����ڵ���������α߳������Ǽ�¼��ijΪ���½ǵ���������α߳���
		��������matrix[i][j]Ϊ0ʱ dp[i][j]Ϊ0��Ϊ1ʱ��������ߡ��ϱߺ����ϱ�����dp��ֵ
		���Ƿֲ���ʾ����������Ϊ���µ���������εı߳������������ε���һ�𣬼���matrix[i][j]Ϊ1���Ϳ������һ�������������
		���������������εı߳�ʱ��������Сֵ+1

	�ܽ�
		���dpֱ�Ӵ�Ŵ�ʱ���ƽ�Ϊ���ѣ����Կ����ö��������Ŵ𰸣�dp��Ϊ�����׵��Ƶ���ʽ
*/
int maximalSquare(vector<vector<char>>& matrix)
{
	/*
		0  0 0 0 0 0

		0  1 0 1 0 0
		0  1 0 1 1 1
		0  1 1 1 1 1
		0  1 0 0 1 0
	*/
	int m = matrix.size();
	int n = matrix[0].size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1;j <= n;++j)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			if (1 == matrix[i - 1][j - 1])
			{
				int side = 1 + dp[i][j];
				if (i >= side && j >= side)
				{
					bool foundzero = false;
					for (int x = i - side; x < i; ++x)
					{
						for (int y = j - side; y < j; ++y)
						{
							if (0 == matrix[x][y])
							{
								foundzero = true;
								break;
							}
						}

						if (foundzero)break;
					}

					if (!foundzero)
					{
						dp[i][j] = side;
					}
				}
			}
		}
	}

	return dp[m][n] * dp[m][n];
}

int maximalSquare2(vector<vector<char>>& matrix)
{
	/*
		0  0 0 0 0 0

		0  1 0 1 0 0
		0  1 0 1 1 1
		0  1 1 1 1 1
		0  1 0 0 1 0
	*/
	int m = matrix.size();
	int n = matrix[0].size();
	int max_side = 0;
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1;j <= n;++j)
		{
			if (1 == matrix[i - 1][j - 1])
			{
				dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
				max_side = max(max_side, dp[i][j]);
			}
			else
			{
				dp[i][j] = 0;
			}
		}
	}

	return max_side * max_side;
}

int test221()
{
	vector<vector<char>>matrix
	{
		{ 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0 },
	};

	return maximalSquare2(matrix);
}