#pragma once
#include <vector>
#include <functional>

/*
	穷举求值：动态规划的本质是穷举，因此一定存在循环
	
	重叠子问题：在穷举求解的过程种，存在重复求解的子问题，可以保存好求解过的答案，然后直接使用
	
	最优子结构：问题分解后的子问题是独立的，其值只有一方影响另一方而不能互相影响
	
	状态转移方程：具体的子问题的依赖关系

	类型：
		备忘录递归：在穷举递归的基础上增加备忘录数组，如果备忘录保存了已求解的值则直接返回，否则继续求解
		dp迭代：将递归转为迭代，依然使用一个数组保存已求解的值
*/

// 备忘录递归
int question(const std::vector<int>& nums)
{
	std::vector<int> memo(nums.size(), -1);
	std::function<int(int)> dp = [&](int i)
		{
			// 其他条件...
			
			// 已经求解过并保存在memo，直接返回
			if (-1 != memo[i])
			{
				return memo[i];
			}

			for (auto el : nums)
			{
				int res = dp(el);

				//... 计算结果

				memo[el] = res;
			}

			return memo[i];
		};

	return dp(nums.size() - 1);
}

// dp迭代（一维单循环）
int question(const std::vector<int>& nums)
{
	std::vector<int> dp(nums.size(), -1);

	for (int i = 0;i < nums.size();++i)
	{
		int res = -1;

		//... 计算结果

		dp[i] = res;
	}

	return dp[nums.size() - 1];
}