#pragma once
#include "../base_header.h"
/*
	一次遍历9*9的方格
	每个方格从可选取的数字中选一个，然后进入下一层
	从下层返回后，撤销选择

	难点在于如何选择方格所在的3*3的chunk

	对于坐标(i, j) 其所在的chunk的左上角的坐标为： (i / 3 * 3 , j / 3 * 3);
	从chunk的左上角开始遍历整个chunk，每个chunk的左边为：
		k:0~8
		(i / 3 * 3 + k / 3, j / 3 * 3 + k % 3)
*/

void solveSudoku(vector<vector<char>>& board)
{
	bool found = false;

	// 将所在行、所在列、所在chunk的已用过的数字存下
	// 也可以不保存，而是在每格重新计算，因为循环只有9，不浪费性能
	short masks_chunk[9];
	short masks_row[9];
	short masks_col[9];
	memset(&masks_chunk, 0, sizeof(masks_chunk));
	memset(&masks_row, 0, sizeof(masks_row));
	memset(&masks_col, 0, sizeof(masks_col));

	for(int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
		{
			masks_chunk;
			auto v = board[i][j];
			if ('.' != v)
			{
				masks_row[i] |= (1 << (v - '1'));
				masks_col[j] |= (1 << (v - '1'));
				masks_chunk[i / 3 * 3 + j / 3] |= (1 << (v - '1'));
			}
		}

	auto dfs = [&](this auto&& dfs, int i, int j)
		{
			if (found)return;
			if (8 <= i && 9 <= j) // 达到终点，完成计算
			{
				found = true;
				return;
			}

			if (j >= 9) // 换行
			{
				++i, j = 0;
			}

			if ('.' == board[i][j])
			{
				for (auto c = 0; c < 9; ++c)
				{
					if (masks_row[i] & (1 << c)
						|| masks_col[j] & (1 << c)
						|| masks_chunk[i / 3 * 3 + j / 3] & (1 << c))continue;// 数字已用过，则跳过

					board[i][j] = c + '1';
					masks_row[i] |= (1 << c);
					masks_col[j] |= (1 << c);
					masks_chunk[i / 3 * 3 + j / 3] |= (1 << c);

					dfs(i, j + 1);
					if (found)return;
					board[i][j] = '.';
					masks_row[i] &= ~(1 << c);
					masks_col[j] &= ~(1 << c);
					masks_chunk[i / 3 * 3 + j / 3] &= ~(1 << c);
				}
			}
			else
			{
				dfs(i, j + 1);
			}
		};

	dfs(0, 0);
}