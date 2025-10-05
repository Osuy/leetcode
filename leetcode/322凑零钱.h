#pragma once
#include "base_header.h"
/*
	凑零钱
	给出n种零钱，求能凑数指定数目的最小硬币数
	“子集和 = 某值”的题型的变体，需要求的不是是否能，而是最小数量，每个零钱可以重复

	问题的解由硬币种类n和数额amount决定。
	对于子问题 i种硬币 凑 k 数额，其最小的数量依赖于
		1.coins[i]> k, 解 = i-1种硬币凑k
		2.i种硬币凑k-coins[i]
	可见存在重叠子问题

	许久后再次答题，不能答出。需牢记以下重点：
	一、求“使用前i种硬币凑额度j的最少数量”时，若额度j - coins[i]时，再加上一枚coins[i]，就是一个答案
		由于已经求出“使用前i-1种硬币凑额度为j的最少数量”，至少它也是一个答案，所以要两者取较小值
	二、dp数组的维度一是考虑硬币前i种，维度二是凑出j的额度，这样遍历会更方便
	三、由于子问题使用了加法，但是答案是求最小值，所以不宜初始化为-1，因为-1随着加法会成为正数，而且会干扰求最小值时的答案
		初始化为amount+1更为合适
		因为硬币面值最小是1，所以使用硬币的最大数量是amount，amount+1一定不是答案，所以可以用来初始化

*/

int coinChange(vector<int>& coins, int amount) {
	if (amount <= 0)return 0;
	vector<int> base(amount + 1, amount + 1);
	base[0] = 0;
	vector<vector<int>> dp(coins.size() + 1, base);

	for (int i = 1;i <= coins.size();++i)
	{
		for (int j = 1;j <= amount;++j)
		{
			if (coins[i - 1] > j)
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = std::min(dp[i - 1][j], 1 + dp[i][j - coins[i - 1]]);
			}
		}
	}

	return dp[coins.size()][amount] == amount + 1 ? -1 : dp[coins.size()][amount];
}

/*
	dp优化
	上一种解法使用了二维数组，但是注意到：dp[i][j] 依赖于 dp[i - 1][j]和dp[i][j - coins[i - 1]]。
	即第i行第j个依赖于第i-1行第j个 或第i行第j-coin个。对于同一行，因为coin变化，所以整行的结果都要保留
	对于上一行，只取j相同的那一个，j之前的数据都不需要，因此可以原地覆盖，即优化为一维数组
	内外循环不重要，因为两个依赖的项都在当前项的左上
*/

int coinChange(vector<int>& coins, int amount) {
	if (amount <= 0)return 0;
	vector<int> dp(amount + 1, amount + 1);
	dp[0] = 0;

	for (int i = 1;i <= coins.size();++i)
	{
		for (int j = 1;j <= amount;++j)
		{
			if (coins[i - 1] > j)
			{
				continue;
			}
			
			dp[j] = std::min(dp[j], 1 + dp[j - coins[i - 1]]);
			
		}
	}

	return dp[amount] == amount + 1 ? -1 : dp[amount];
}

/*
	备忘录递归解法，自顶向下递归，遇到求过的问题直接返回
*/
int coinChange3(vector<int>& coins, int amount)
{
	vector<int> memo(amount + 1, amount + 1);

	auto dfs = [&](this auto&& dfs, int rest)->int
		{
			if (rest < 0)return -1;
			if (rest == 0)return 0;

			if (memo[rest] != amount + 1)return memo[rest];
			int res = INT_MAX;
			for (auto el : coins)
			{
				int sub_problem = dfs(rest - el);
				if (sub_problem == -1)continue;
				res = std::min(res, 1 + sub_problem);
			}
			memo[rest] = INT_MAX == res ? -1 : res;
			return memo[rest];
		};
	
	return dfs(amount);
}