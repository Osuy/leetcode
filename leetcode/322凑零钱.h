#pragma once
#include "base_header.h"
/*
	����Ǯ
	����n����Ǯ�����ܴ���ָ����Ŀ����СӲ����
	���Ӽ��� = ĳֵ�������͵ı��壬��Ҫ��Ĳ����Ƿ��ܣ�������С������ÿ����Ǯ�����ظ�

	����Ľ���Ӳ������n������amount������
	���������� i��Ӳ�� �� k �������С������������
		1.coins[i]> k, �� = i-1��Ӳ�Ҵ�k
		2.i��Ӳ�Ҵ�k-coins[i]
	�ɼ������ص�������

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
	dp�Ż�
	��һ�ֽⷨʹ���˶�ά���飬����ע�⵽��dp[i][j] ������ dp[i - 1][j]��dp[i][j - coins[i - 1]]��
	����i�е�j�������ڵ�i-1�е�j�� ���i�е�j-coin��������ͬһ�У���Ϊcoin�仯���������еĽ����Ҫ����
	������һ�У�ֻȡj��ͬ����һ����j֮ǰ�����ݶ�����Ҫ����˿���ԭ�ظ��ǣ����Ż�Ϊһά����
	����ѭ������Ҫ����Ϊ������������ڵ�ǰ�������
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
	����¼�ݹ�ⷨ���Զ����µݹ飬�������������ֱ�ӷ���
*/
int coinChange3(vector<int>& coins, int amount)
{
	vector<int> memo(amount + 1, -2);

	function<int(vector<int>&, int)> dp = [&dp, &memo](vector<int>& coins, int amount)->int
		{
			if (amount < 0)return -1;
			if (amount == 0)return 0;

			if (memo[amount] != -2)return memo[amount];
			int res = INT_MAX;
			for (auto el : coins)
			{
				int sub_problem = dp(coins, amount - el);
				if (sub_problem == -1)continue;
				res = std::min(res, 1 + sub_problem);
			}
			memo[amount] = INT_MAX == res ? -1 : res;
			return memo[amount];
		};
	
	return dp(coins, amount);
}