#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <utility>

#include <iostream>
/*
	求二叉树的自底向上的层序遍历
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
	给出x数组
	遍历数组，如果x大于等于el，则加到x上
	否则，el和x的最大公约数加到x上

	C++17以前如何求最大公约数：
		假设a = nK, b = mk， k是a和b的最大公约数
		则 a-b = (n-m)k，即a-b的最大公约数也是k
		所以递归求解即可
*/

int gcd(int a, int b)
{
	if (0 == b)return a;
	return gcd(b, a % b); // a - b 改为 a % b 效率更好
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
	在n*n的地图里，
		S起点，
		·空地
		O障碍物
		C车
		X终点
	车一秒走一格，人两秒走一格
	求t秒内能否从S到达X
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
	每次只能把某个字符移动到末尾
	求把s转为t的最小次数

	如果保证s和t里出现的字符和数量相等，则
	一定有答案

	将字符串中s[0...len]中的若干的字符移动到末尾，会使s变为
	s的一个子序列s[i..j] + 移动的字符的一个排列
	自学列与t的前段相等，也一定存在一个移动过的字符的排列，与t的后段相等
	而排列的长度就是操作的次数，现在，要使这个排列长度最小，就要使s的子序列的长度最大
	于是就是要求与t的前n个字符相同的最长子序列

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
				dfs(k + 1, j); // [k+1, len) 去匹配 j
				if (s[k] == t[j]) // 如果字符串相等，则让[k+1, len) 去匹配j+1
				{
					dfs(k + 1, j + 1);
				}
			}
		};

	dfs(0, 0);

	return len - max_seq;
}

/*
	从数组取若干元素，使和大于等于b
	求最少数量
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