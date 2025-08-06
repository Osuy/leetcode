#pragma once
#include "../base_header.h"
/*
	��n*n���������n���ʺ�ʹ���ǻ��಻�ṥ��
	�ʺ�Ĺ�����Χ�����ڵ��С��С�б��

	ÿ��ݹ��ڸ����Ϸ���һ���ʺ󡣷��õĿ�ѡ�б���n������ѭ��n��
	ÿ��ѭ���жϸ��и����Ƿ�ɷ���

	ֱ��ȫ���ʺ���ã����һ����
*/

vector<vector<string>> solveNQueens(int n) {

	vector<string> solution(n, string(n, '.'));// ��ʼ������
	vector<vector<string>> ans;
	
	auto could_place = [&](int i, int j) -> bool // �ж�(i, j)�Ƿ�ɷ���
		{
			for (int k = 0; k < i; ++k)
			{
				if ('Q' == solution[k][j]
					|| ((j - (i - k)) >= 0 && 'Q' == solution[k][j - (i - k)])
					|| ((j + (i - k)) < n && 'Q' == solution[k][j + (i - k)]))
				{
					return false;
				}
			}

			return true;
		};

	auto dfs = [&](this auto&& dfs, int i)
		{
			if (i == n)// �ﵽn�У��ҵ���һ���⣬����ans
			{
				ans.push_back(solution);
				return;
			}

			auto& str = solution[i];
			for (int j = 0; j < n; ++j)
			{
				if (!could_place(i, j))continue;

				str[j] = 'Q'; // ���ûʺ�
				dfs(i + 1);
				str[j] = '.'; // ��������
			}
		};

	dfs(0);

	// ������
	// ���ڵ�����Ҫ�ں���������������ڴ����������ѡ��������Ҫһ�����������
	vector<int> indics(n, -1);
	int i = 0;
	while (i >= 0) // ���i�˻ص���-1���ҳ������еĴ𰸣�����ѭ��
	{
		if (n == i)
		{
			// �ҵ�һ���𰸣��ص���һ��
			ans.push_back(solution);
			--i;
			continue;
		}

		if (indics[i] >= 0 && indics[i] < n)
		{
			solution[i][indics[i]] = '.';
		}

		do indics[i]++; while (!could_place(i, indics[i]) && indics[i] < n);

		if (indics[i] < n)
		{
			solution[i][indics[i]] = 'Q';
			
			++i;
		}
		else
		{
			// �ص���һ�㣬������һ��Ļʺ��ѡ�б�
			solution[i] = string(n, '.');
			indics[i] = -1;
			--i;
		}
	}

	return ans;
}