#pragma once
#include "../base_header.h"

/*
	200.��������
	�������������ÿ�����꣬����������Ԫ��Ϊ1����˵�������ǵ����һ����
	dfs�����õ��죬�����û��ֵ��Ϊ0��
	�����������ĺ��������У���������ͬ��������������֡�������������ѭ����û�˼������죬�𰸾��Ǽ�
*/

int numIslands(vector<vector<char>>& grid) {
	auto row = grid.size();
	auto col = grid[0].size();

	// dfs���������û����
	auto dfs = [&](this auto&& dfs, int i, int j)->void
		{
			// ��߽��0��������ı߽磬�򷵻�
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

	// ����ÿ�����꣬���ֵΪ1��˵��������һ����δ��û�ĵ���res++
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
	1254 ��յ�������
	1Ϊˮ��0Ϊ½�أ���1��Χ�ĵ��������
	�߽粻��Ϊ��Χ

	���ڱ߽粻��Ϊ��Χ����������һ��0ʱ��Ҫ������ʼdfs��bfs����������ڵĵ������߽��Ƿ�Ϊ1
	Ϊ�˱�������ظ�����0������ʹ��visited���飬��Ȼ�������ֱ�ӽ�0��Ϊ1
	��Ϊ������0��Ϊ1������Ӱ��õ����Ƿ��Ǵ𰸡������0��������߽����ڣ����0���Ǵ𰸣����Ը�0���ڵ����嶼���Ǵ�
	�������0����߽����ڣ����Ϊ1ֻ�ǵ�����������ٴα�����Ҳ��Ӱ���0���ڵ������Ƿ��Ǵ�

	��һ�ֽⷨ���򵥣���������200�ĳ�û����
	�ȱ����߽��ϵ�0�������ǳ�û����ôʣ�µĵ���Ͷ��Ǳ�1��Χ��
	Ȼ���ٱ��������ľ��������������
*/

int closedIsland(vector<vector<int>>& grid) {

    auto row = grid.size();
    auto col = grid[0].size();
    //vector<vector<bool>> visited(row, vector<bool>(col, false));
    auto dfs = [&](this auto&& dfs, int i, int j)->bool
        {
			// ���磬���Ǵ𰸣�false
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
				// ���� && ���·���㣬���Ա���ֿ�����ÿ�����򶼱���
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

	// �ⷨ2����200һ���ĳ�û����
	auto dfs2 = [&](this auto&& dfs2, int i, int j)->void
		{
			// ��߽��0��������ı߽磬�򷵻�
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

	// �ѱ߽�ĵ����û
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

	// ʣ�µĵ�����Ƿ�յ���
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
	1020 �ɵص�����
	0��ʾˮ��1��ʾ½�أ�����߽���ͨ��½�ص�����

	�������������1������count
	Ȼ���û��߽����ڵĵ��죬��û��ͬʱ��count���ٳ�û��1������
	ʣ�µľ��Ǵ�
*/

int numEnclaves(vector<vector<int>>& grid) {
	auto row = grid.size();
	auto col = grid[0].size();

	// ��1������
	int count = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (grid[i][j])count++;
		}
	}

	// ��û������ÿ�γ�ûһ��ͼ���1������
	auto dfs = [&](this auto&& dfs, int i, int j)->void
		{
			// ��߽��0��������ı߽磬�򷵻�
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

	// ��û���ߵĵ��죬ʣ�µľ��Ǵ�
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
	695 ��������
	ͬ����û���죬����ÿ�γ�û�ͼ�¼����Ĵ�С++
	ȡ���ĵ�������
*/

int maxAreaOfIsland(vector<vector<int>>& grid) {
	auto row = grid.size();
	auto col = grid[0].size();
	// ��û����������ֵ�Ǹó�û��������
	auto dfs = [&](this auto&& dfs, int i, int j)->int
		{
			// �ﵽ�߽��0������û�����Ϊ0
			if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == 0)
			{
				return 0;
			}

			// ��û������
			grid[i][j] = 0;
			// �ܳ�û��� = 1 + ����Χ�ĸ������û�����
			return 1 + dfs(i, j + 1) + dfs(i, j - 1) + dfs(i + 1, j) + dfs(i - 1, j);
		};

	int ans = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			// ����1����û��ȡ���ֵ
			if (grid[i][j])
			{
				ans = max(ans, dfs(i, j));
			}
		}
	}

	return ans;
}

/*
	1905 �ӵ�������
	����ϵ���еĽ����⣬������Ȼ���е�
	����֮ǰ����Ŀ��Ҫ˼���ø���һЩ

	������ȻҪ��һ����û�����������ų��Ѿ�������ĵ�
	��Ҫ��һ�������ĵ���û���߼���֮ǰһ��
	�������ڣ�����Ҫ����grid1���ж��Ƿ����ӵ���
*/

int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2)
{
	auto row = grid1.size();
	auto col = grid1[0].size();

	// ��û�����������Ƿ���grid1���ӵ���
	auto dfs = [&](this auto&& dfs, int i, int j)->bool
		{
			if (i >= row || j < 0 || i < 0 || j >= col || !grid2[i][j])
			{
				return true;
			}

			grid2[i][j] = 0;

			// ��ʼֵ��grid1��Ӧֵ�Ƿ��ǵ��죬������ǣ���˵���Ҳ����
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
			if (grid2[i][j] && dfs(i, j))// �ǵ��������ӵ�����ans++
			{
				++ans;
			}
		}
	}
	return ans;
}