#pragma once
#include "base_header.h"
/*
	����
	
	����Ʊ�൱�ڶ�һ���Ӿ������ÿ��Ԫ������ͬ���������ǿ������뵽�ֲ
	����һά�������
		��һά���߶��������߶Σ����������߶α��������ұ�ռ�õĵ㲻���̵�
		��ʼ���ֲ�����
		�����߶Σ��Էֲ�������ǰN��ͣ���������βʱ���ǡ��Ϊ0�������̡�
		�����жϲ��̵���ռ�õĵ㡣
		�ڱ���ʱ�������cur>0�������������1��������cur=0�������������0����false

	��չ����ά��
		��һ���Ӿ���(x,y,i,j)������Ԫ������ͬ����f����Ч�� f(0,0,x,y) + f(0��0��i,j,)  - f(0,0,i,y)  - f(0,0,x,j)
		���磬���Ӿ������ÿ��Ԫ��+1���൱��[x,y]+1,[x,j]-1,[i,y]-1, [i][j] +1
		�� ��һ�������diff���άǰ׺�ͣ����Ϊ������˵���������ڣ����Ϊ0��˵����������

	�ܷ�����Ʊ����i,j,i+width,j+height �����ڵ����� Ԫ��֮���Ƿ�Ϊ0�������ö�άǰ׺�����

	����Ʊ���� i,j,i+width,j+height cnt �����ڵ�����Ԫ��+1������ת��Ϊ �� ������ĸ���� diff����
		��diff��ǰ׺�ͣ��������һ�����cntΪ0����gridֵҲΪ0���������û��ռ�õ���Ҳû����Ʊ
*/
class Solution {
public:

	bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) 
	{
		int row = grid.size(), col = grid[0].size();

		// ����һ��col+1, row+1�ľ���sums[y][x] ��ʾ��xyΪ���½ǵĿ�����ڵ�ľ����
		vector<vector<int>> sums(row + 1, vector<int>(col + 1));

		for (int y = 0; y < row; ++y)
		{
			for (int x = 0; x < col; ++x)
			{
				sums[y + 1][x  +  1] = grid[y][x] + sums[y + 1][x] + sums[y][x + 1] - sums[y][x];
			}
		}

		vector<vector<int>> diff(row + 2, vector<int>(col + 2));
		for (int y = 0; y < row - stampHeight + 1; ++y)
		{
			for (int x = 0; x < col - stampWidth + 1; ++x)
			{
				if (0 == sums[y][x] + sums[y + stampHeight][x + stampWidth] - sums[y][x + stampWidth] - sums[y + stampHeight][x])
				{
					++diff[y + 1][x + 1];
					++diff[y + 1 + stampHeight][x + 1 + stampWidth];
					--diff[y + 1 + stampHeight][x + 1];
					--diff[y + 1][x + 1 + stampWidth];
				}
			}
		}

		// ��diff��ǰ׺�ͣ������Ϊ0��gridҲΪ0��false
		for (int y = 0; y < row; ++y)
		{
			for (int x = 0; x < col; ++x)
			{
				diff[y + 1][x + 1] += diff[y][x + 1] + diff[y + 1][x] - diff[y][x];
				if (0 == diff[y + 1][x + 1] && 0 == grid[y][x])
				{
					return false;
				}
			}
		}

		return true;
	}
};

/*
	���ѵ���д��

	ij��������
*/

class Solution2 {
public:
	bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) 
	{
		int n = grid.size();
		int m = grid[0].size();
		vector<int> col(m, 0);
		vector<int> row(m, 0);
		int totalZero = 0;
		int stampedZero = 0;

		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < m; j++) 
			{
				if (grid[i][j] == 1) // ���gridֵΪ1������j��j��Ϊ0�����൱�����¿�ʼ��������
				{
					col[j] = 0;
					row[j] = 0;
				}
				else 
				{
					totalZero++;//�ۼ�0ֵ
					col[j]++;// ��j�е���ֵ��++
					if (col[j] >= stampHeight) // �����ֵ���ڵ��ڸ߶ȣ����Լ���������Ʊ��ȣ�������ֵΪ0
					{
						row[j] = 1 + (j > 0 ? row[j - 1] : 0);// ����ֵ�����ۼ�
						if (row[j] >= stampWidth) 
						{
							//�����ֵ���ڿ�ȣ�˵�����Կ�������Ʊ
							// ��ij������ i-height,j - width
							for (int jj = j; jj > j - stampWidth && grid[i][jj] == 0; jj--)
							{
								for (int ii = i; ii > i - stampHeight && grid[ii][jj] == 0; ii--) 
								{
									grid[ii][jj] = 1;
									stampedZero++;
								}
							}
						}
					}
					else 
					{
						row[j] = 0;
					}
				}
			}
		}

		return totalZero == stampedZero;
	}
};