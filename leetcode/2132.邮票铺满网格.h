#pragma once
#include "base_header.h"
/*
	困难
	
	贴邮票相当于对一个子矩阵里的每个元素做相同操作，于是可以联想到分差。
	考虑一维的情况：
		在一维的线段上贴子线段，最终整个线段被铺满，且被占用的点不被铺到
		初始化分差数组
		遍历线段，对分差数组求前N项和，便利到结尾时如果恰好为0，则满铺。
		还需判断不铺到被占用的点。
		在便利时，如果在cur>0的情况下碰到了1，或者在cur=0的情况下碰到了0，则false

	扩展到二维：
		对一个子矩阵(x,y,i,j)的所有元素做相同操作f，等效于 f(0,0,x,y) + f(0，0，i,j,)  - f(0,0,i,y)  - f(0,0,x,j)
		例如，对子矩阵里的每个元素+1，相当于[x,y]+1,[x,j]-1,[i,y]-1, [i][j] +1
		用 另一个数组对diff求二维前缀和，如果为正数，说明在区间内，如果为0，说明在区间外

	能否贴邮票：以i,j,i+width,j+height 矩阵内的所有 元素之和是否为0，可以用二维前缀和求得

	贴邮票：对 i,j,i+width,j+height cnt 矩阵内的所有元素+1，可以转化为 对 矩阵的四个点的 diff操作
		对diff求前缀和，如果存在一个点的cnt为0，且grid值也为0，则这个点没被占用但是也没贴邮票
*/
class Solution {
public:

	bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) 
	{
		int row = grid.size(), col = grid[0].size();

		// 创建一个col+1, row+1的矩阵，sums[y][x] 表示以xy为右下角的开区间节点的矩阵和
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

		// 对diff求前缀和，如果和为0且grid也为0则false
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
	网友的神级写法

	ij遍历矩阵，
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
				if (grid[i][j] == 1) // 如果grid值为1，则令j行j列为0？，相当于重新开始计算行列
				{
					col[j] = 0;
					row[j] = 0;
				}
				else 
				{
					totalZero++;//累加0值
					col[j]++;// 把j行的列值都++
					if (col[j] >= stampHeight) // 如果列值大于等于高度，可以继续考虑邮票宽度，否则行值为0
					{
						row[j] = 1 + (j > 0 ? row[j - 1] : 0);// 对行值进行累加
						if (row[j] >= stampWidth) 
						{
							//如果行值大于宽度，说明可以可以贴邮票
							// 从ij遍历到 i-height,j - width
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