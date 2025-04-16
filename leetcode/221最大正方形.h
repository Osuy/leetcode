#pragma once
#include "base_header.h"
/*
	难度：中等
	在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积

	考虑以ij为右下角的矩阵，
	其区域内的最大正方形边长side = max（ i-1 j 区域内的最大正方形，i j-1 区域内的最大正方形）
	如果matrix[i][j]为1，则可以考虑side+1， 于是去遍历side+1区域内的矩阵元素，如果全为1，则说明存在side+1边长的正方形，这个正方形更大

	方法二：
		上文提到的方法，要遍历side + 1的区域，耗时较多，可以修改dp含义来优化。由于要求的是最大正方形（边长）
		原本dp[i][j]记录的就是最大正方形边长，但是遍历过程种，可以额外用一个变量max_side来记录，因此dp就可以去存放其他数据
		优化后的dp不记录区域内的最大正方形边长，而是记录以ij为右下角的最大正方形边长。
		这样，当matrix[i][j]为0时 dp[i][j]为0。为1时，考虑左边、上边和左上边三个dp的值
		它们分布表示了以三个点为右下的最大正方形的边长。三个正方形叠在一起，加上matrix[i][j]为1，就可以组成一个更大的正方形
		而这个更大的正方形的边长时三个的最小值+1

	总结
		如果dp直接存放答案时地推较为困难，可以考虑用额外变量存放答案，dp改为更容易递推的形式
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