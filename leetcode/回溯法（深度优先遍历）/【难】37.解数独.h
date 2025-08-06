#pragma once
#include "../base_header.h"
/*
	һ�α���9*9�ķ���
	ÿ������ӿ�ѡȡ��������ѡһ����Ȼ�������һ��
	���²㷵�غ󣬳���ѡ��

	�ѵ��������ѡ�񷽸����ڵ�3*3��chunk

	��������(i, j) �����ڵ�chunk�����Ͻǵ�����Ϊ�� (i / 3 * 3 , j / 3 * 3);
	��chunk�����Ͻǿ�ʼ��������chunk��ÿ��chunk�����Ϊ��
		k:0~8
		(i / 3 * 3 + k / 3, j / 3 * 3 + k % 3)
*/

void solveSudoku(vector<vector<char>>& board)
{
	bool found = false;

	// �������С������С�����chunk�����ù������ִ���
	// Ҳ���Բ����棬������ÿ�����¼��㣬��Ϊѭ��ֻ��9�����˷�����
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
			if (8 <= i && 9 <= j) // �ﵽ�յ㣬��ɼ���
			{
				found = true;
				return;
			}

			if (j >= 9) // ����
			{
				++i, j = 0;
			}

			if ('.' == board[i][j])
			{
				for (auto c = 0; c < 9; ++c)
				{
					if (masks_row[i] & (1 << c)
						|| masks_col[j] & (1 << c)
						|| masks_chunk[i / 3 * 3 + j / 3] & (1 << c))continue;// �������ù���������

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