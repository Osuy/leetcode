#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <utility>

#include <iostream>
/*
	����������Ե����ϵĲ������
*/
namespace yanyun
{
struct TreeNode
{
	int val = 0;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};
std::vector<std::vector<int>> levelOrderBottom(TreeNode* root)
{
	std::queue<TreeNode*> q{};
	q.push(root);
	std::vector<std::vector<int>> ans{};

	while (!q.empty())
	{
		auto size = q.size();
		std::vector<int> level{};
		level.reserve(size);
		while (size--)
		{
			auto node = q.front();
			q.pop();

			if (!node)continue;
			level.push_back(node->val);

			q.push(node->left);
			q.push(node->right);
		}
		if (!level.empty())
		{
			ans.emplace(ans.begin(), std::move(level));
		}
	}

	return ans;
}

/*
	����x����
	�������飬���x���ڵ���el����ӵ�x��
	����el��x�����Լ���ӵ�x��

	C++17��ǰ��������Լ����
		����a = nK, b = mk�� k��a��b�����Լ��
		�� a-b = (n-m)k����a-b�����Լ��Ҳ��k
		���Եݹ���⼴��
*/

int gcd(int a, int b)
{
	if (0 == b)return a;
	return gcd(b, a % b); // a - b ��Ϊ a % b Ч�ʸ���
}

int battleNum(int x, const std::vector<int>& nums)
{
	for (auto el : nums)
	{
		if (x < el)
		{
			x += gcd(x, el);
		}
		else
		{
			x += el;
		}
	}

	return x;
}

/*
	��n*n�ĵ�ͼ�
		S��㣬
		���յ�
		O�ϰ���
		C��
		X�յ�
	��һ����һ����������һ��
	��t�����ܷ��S����X
*/

bool has_safe_route(std::vector<std::vector<char>>& board, const int limit)
{
	int time_per_block = 2;
	auto row = board.size();
	auto col = board[0].size();
	int min_used = INT_MAX;
	std::unordered_map<int, bool> visited;
	auto dfs = [&](this auto&& dfs, int i, int j, int time)->bool
		{
			if (i < 0 || i >= row || j < 0 || j >= col || 'O' == board[i][j])
			{
				return false;
			}

			auto key = (i << 24) | (j << 16) | time;
			if (visited.contains(key))
			{
				return visited[key];
			}

			if (time > limit)
			{
				visited[key] = false;
				return false;
			}

			if ('X' == board[i][j])
			{
				min_used = std::min(min_used, time);
				visited[key] = true;
				return true;
			}

			auto old_speed = time_per_block;
			if ('C' == board[i][j])
			{
				time_per_block = 1;
			}

			auto old_block = board[i][j];
			board[i][j] = 'O';

			auto ret = dfs(i - 1, j, time + time_per_block);
			ret |= dfs(i + 1, j, time + time_per_block);
			ret |= dfs(i, j - 1, time + time_per_block);
			ret |= dfs(i, j + 1, time + time_per_block);

			time_per_block = old_speed;
			board[i][j] = old_block;

			return ret;
		};

	bool found = false;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if ('S' == board[i][j])
			{
				found = dfs(i, j, 0);
				break;
			}
		}
	}

	return found;
}

/*
	ÿ��ֻ�ܰ�ĳ���ַ��ƶ���ĩβ
	���sתΪt����С����

	�����֤s��t����ֵ��ַ���������ȣ���
	һ���д�

	���ַ�����s[0...len]�е����ɵ��ַ��ƶ���ĩβ����ʹs��Ϊ
	s��һ��������s[i..j] + �ƶ����ַ���һ������
	��ѧ����t��ǰ����ȣ�Ҳһ������һ���ƶ������ַ������У���t�ĺ�����
	�����еĳ��Ⱦ��ǲ����Ĵ��������ڣ�Ҫʹ������г�����С����Ҫʹs�������еĳ������
	���Ǿ���Ҫ����t��ǰn���ַ���ͬ���������

*/

int min_transform_times(const std::string& s, const std::string& t)
{
	int counts[26];
	memset(&counts, 0, sizeof(counts));

	for (auto el : s)
	{
		counts[el - 'a']++;
	}

	for (auto el : t)
	{
		counts[el - 'a']--;
	}

	if (std::any_of(counts, counts + 26, [](const int c) { return 0 != c; }))
	{
		return -1;
	}

	auto len = s.length();

	std::vector<std::vector<int>> dp(len + 1, std::vector<int>(len + 1, 0));

	/*
		0 a b c d e
		a 1 1 1 1 1
		b 1 2 2 2 2
		e 1 2 2 2 2
		d 1 2 2 2 2
		c 1 2 3 3 3
	*/

	for (int i = 1; i <= len; ++i)
	{
		for (int j = 1; j <= len; ++j)
		{
			auto seq_len = dp[i - 1][j - 1];
			if (t[seq_len] == s[i - 1])
			{
				seq_len += 1;
			}

			dp[i][j] = std::max(seq_len, std::max(dp[i - 1][j], dp[i][j - 1]));
		}
	}

	int max_seq = 0;
	auto dfs = [&](this auto&& dfs, int i, int j)
		{
			if (i >= len)
			{
				max_seq = max(max_seq, j);
				return;
			}

			for (int k = i; k < len; ++k)
			{
				dfs(k + 1, j); // [k+1, len) ȥƥ�� j
				if (s[k] == t[j]) // ����ַ�����ȣ�����[k+1, len) ȥƥ��j+1
				{
					dfs(k + 1, j + 1);
				}
			}
		};

	dfs(0, 0);

	return len - max_seq;
}

/*
	������ȡ����Ԫ�أ�ʹ�ʹ��ڵ���b
	����������
*/

int minSumAboveB(std::vector<int>& nums, int b)
{
	std::sort(nums.begin(), nums.end());

	int count = 0;
	auto it = nums.rbegin();
	while (b > 0 && it != nums.rend())
	{
		b -= *it;
		it.operator++();
	}

	return count;
}

void test()
{
	std::cout << min_transform_times("abcdef", "abedcf");
}
}