#pragma once
#include "base_header.h"
/*
	难度：中等
	查找矩阵中是否存在target

	和378查找矩阵在第k小的数类似。只不过这题仅仅只是它的一个工具函数
	把求左上三角的函数改造一下：当遇到target则return true

	大体步骤是：从左下角开始找该列第一个不大于target的数val，如果就是target，则真
	否则平移到下一列
	如此遍历出一条路径，这条路径构成的左上角内的元素都是小于target的，而target要么不存在，要么出现在这条路径上
*/

bool searchMatrix(vector<vector<int>>& matrix, int target) {
	int x = 0;
	int y = matrix.size() - 1;
	while (x < matrix[0].size())
	{
		while (y >= 0 && matrix[y][x] > target)
		{
			--y;
		}
		if (y >= 0 && target == matrix[y][x])return true;
		++x;
	}

	return false;
}