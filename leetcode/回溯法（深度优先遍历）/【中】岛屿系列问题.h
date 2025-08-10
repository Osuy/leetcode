#pragma once
#include "../base_header.h"

/*
	200.求岛屿数量
	在主函数里遍历每个坐标，如果该坐标的元素为1，则说明可能是岛屿的一部分
	dfs遍历该岛屿，将其沉没（值设为0）
	所以主函数的后续遍历中，不会遇到同个岛屿的其他部分。于是主函数的循环沉没了几个岛屿，答案就是几
*/

int numIslands(vector<vector<char>>& grid) {
	auto row = grid.size();
	auto col = grid[0].size();

	// dfs函数负责沉没岛屿
	auto dfs = [&](this auto&& dfs, int i, int j)->void
		{
			// 外边界或0，即岛屿的边界，则返回
			if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == '0')
			{
				return;
			}

			grid[i][j] = '0';

			dfs(i, j + 1);
			dfs(i + 1, j);
			dfs(i, j - 1);
			dfs(i - 1, j);
		};

	int res = 0;

	// 遍历每个坐标，如果值为1，说明遇到了一个还未沉没的岛，res++
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (grid[i][j] == '1')
			{
				res++;
				dfs(i, j);
			}
		}
	}
	return res;
}

/*
	1254 封闭岛屿数量
	1为水，0为陆地，求被1包围的岛屿的数量
	边界不视为包围

	由于边界不视为包围，所以遇到一个0时，要从它开始dfs或bfs，求出它所在的岛屿的外边界是否都为1
	为了避免遍历重复过的0，可以使用visited数组，当然此题可以直接将0改为1
	因为单个的0改为1，不会影响该岛屿是否是答案。如果该0本来就与边界相邻，则该0不是答案，所以该0所在的整体都不是答案
	而如果该0不与边界相邻，则改为1只是单纯避免后续再次遍历，也不影响该0所在的整体是否是答案

	另一种解法更简单，就是利用200的沉没函数
	先遍历边界上的0，把它们沉没，那么剩下的岛屿就都是被1包围的
	然后再遍历完整的矩阵，求出岛屿数量
*/

int closedIsland(vector<vector<int>>& grid) {

    auto row = grid.size();
    auto col = grid[0].size();
    //vector<vector<bool>> visited(row, vector<bool>(col, false));
    auto dfs = [&](this auto&& dfs, int i, int j)->bool
        {
			// 出界，不是答案，false
            if (i < 0 || j < 0 || i >= row || j >= col)
            {
                return false;
            }

            if (grid[i][j])
            {
                return true;
            }
            else
            {
                grid[i][j] = 1;
                auto ret = true;
				// 由于 && 会短路计算，所以必须分开，对每个方向都遍历
                ret &= dfs(i, j + 1);
                ret &= dfs(i + 1, j);
                ret &= dfs(i, j - 1);
                ret &= dfs(i - 1, j);
                return ret;
            }

        };

    int ans = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (!grid[i][j] && dfs(i, j))
            {
                ++ans;
            }
        }
    }

    return ans;

	// 解法2。和200一样的沉没函数
	auto dfs2 = [&](this auto&& dfs2, int i, int j)->void
		{
			// 外边界或0，即岛屿的边界，则返回
			if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == 1)
			{
				return;
			}

			grid[i][j] = 1;

			dfs2(i, j + 1);
			dfs2(i + 1, j);
			dfs2(i, j - 1);
			dfs2(i - 1, j);
		};

	// 把边界的岛屿沉没
	for (int i = 0; i < row; ++i)
	{
		dfs2(i, 0);
		dfs2(i, col - 1);
	}
	for (int i = 0; i < col; ++i)
	{
		dfs2(0, i);
		dfs2(row - 1, i);
	}

	// 剩下的岛屿就是封闭岛屿
	ans = 0;
	for (int i = 1; i < row - 1; ++i)
	{
		for (int j = 1; j < col - 1; ++j)
		{
			if (!grid[i][j])
			{
				++ans;
				dfs(i, j);
			}
		}
	}

	return ans;
}

/*
	1020 飞地的数量
	0表示水，1表示陆地，求不与边界连通的陆地的数量

	可以先求出所有1的数量count
	然后沉没与边界相邻的岛屿，沉没的同时，count减少沉没的1的数量
	剩下的就是答案
*/

int numEnclaves(vector<vector<int>>& grid) {
	auto row = grid.size();
	auto col = grid[0].size();

	// 求1的数量
	int count = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (grid[i][j])count++;
		}
	}

	// 沉没函数，每次沉没一格就减少1的数量
	auto dfs = [&](this auto&& dfs, int i, int j)->void
		{
			// 外边界或0，即岛屿的边界，则返回
			if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == 0)
			{
				return;
			}

			grid[i][j] = 0;
			count--;

			dfs(i, j + 1);
			dfs(i + 1, j);
			dfs(i, j - 1);
			dfs(i - 1, j);
		};

	// 沉没靠边的岛屿，剩下的就是答案
	for (int i = 0; i < row; ++i)
	{
		dfs(i, 0);
		dfs(i, col - 1);
	}
	for (int i = 0; i < col; ++i)
	{
		dfs(0, i);
		dfs(row - 1, i);
	}

	return count;
}

/*
	695 最大岛屿面积
	同样沉没岛屿，并且每次沉没就记录岛屿的大小++
	取最大的岛屿的面积
*/

int maxAreaOfIsland(vector<vector<int>>& grid) {
	auto row = grid.size();
	auto col = grid[0].size();
	// 沉没函数，返回值是该沉没岛屿的面积
	auto dfs = [&](this auto&& dfs, int i, int j)->int
		{
			// 达到边界或0，不沉没，面积为0
			if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == 0)
			{
				return 0;
			}

			// 沉没该坐标
			grid[i][j] = 0;
			// 总沉没面积 = 1 + 它周围四个方向沉没的面积
			return 1 + dfs(i, j + 1) + dfs(i, j - 1) + dfs(i + 1, j) + dfs(i - 1, j);
		};

	int ans = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			// 遇到1，沉没，取最大值
			if (grid[i][j])
			{
				ans = max(ans, dfs(i, j));
			}
		}
	}

	return ans;
}

/*
	1905 子岛屿数量
	岛屿系列中的较难题，不过仍然是中等
	比起之前的题目，要思考得更多一些

	首先依然要有一个沉没函数，负责排除已经遍历或的岛
	它要把一个完整的岛沉没，逻辑和之前一样
	区别在于，还需要根据grid1来判断是否是子岛屿
*/

int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2)
{
	auto row = grid1.size();
	auto col = grid1[0].size();

	// 沉没函数，返回是否是grid1的子岛屿
	auto dfs = [&](this auto&& dfs, int i, int j)->bool
		{
			if (i >= row || j < 0 || i < 0 || j >= col || !grid2[i][j])
			{
				return true;
			}

			grid2[i][j] = 0;

			// 初始值是grid1对应值是否是岛屿，如果不是，则此岛屿也不是
			auto ret = grid1[i][j];
			ret &= dfs(i, j + 1);
			ret &= dfs(i, j - 1);
			ret &= dfs(i + 1, j);
			ret &= dfs(i - 1, j);
			return ret;
		};

	int ans = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (grid2[i][j] && dfs(i, j))// 是岛屿且是子岛屿则ans++
			{
				++ans;
			}
		}
	}
	return ans;
}