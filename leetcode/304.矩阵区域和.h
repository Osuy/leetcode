#pragma once
#include <vector>
using std::vector;

class NumMatrix {
	vector<vector<int>> sums;
public:
	NumMatrix(vector<vector<int>>& matrix)
	{
		sums.resize(matrix.size());
		sums[0].resize(matrix[0].size());
		sums[0][0] = matrix[0][0];
		for (int row = 1;row < matrix.size();++row)
		{
			sums[row].resize(matrix[row].size());
			sums[row][0] = sums[row - 1][0] + matrix[row][0];
		}

		for (int col = 1;col < matrix[0].size();++col)
		{
			sums[0][col] = sums[0][col - 1] + matrix[0][col];
		}

		for (int row = 1;row < matrix.size();++row)
		{
			for (int col = 1;col < matrix[row].size();++col)
			{
				sums[row][col] = matrix[row][col] + sums[row - 1][col] + sums[row][col - 1] - sums[row - 1][col - 1];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2)
	{
		if (0 < row1)
		{
			if (0 < col1)
			{
				return sums[row2][col2] + sums[row1 - 1][col1 - 1] - sums[row2][col1 - 1] - sums[row1 - 1][col2];
			}
			else
			{
				return sums[row2][col2] - sums[row1 - 1][col2];
			}
		}
		else
		{
			if (0 < col1)
			{
				return sums[row2][col2] - sums[row2][col1 - 1];
			}
			else
			{
				return sums[row2][col2];
			}
		}
	}
};