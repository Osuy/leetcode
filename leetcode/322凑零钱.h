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

	��ú��ٴδ��⣬���ܴ�������μ������ص㣺
	һ����ʹ��ǰi��Ӳ�Ҵն��j������������ʱ�������j - coins[i]ʱ���ټ���һöcoins[i]������һ����
		�����Ѿ������ʹ��ǰi-1��Ӳ�Ҵն��Ϊj��������������������Ҳ��һ���𰸣�����Ҫ����ȡ��Сֵ
	����dp�����ά��һ�ǿ���Ӳ��ǰi�֣�ά�ȶ��Ǵճ�j�Ķ�ȣ����������������
	��������������ʹ���˼ӷ������Ǵ�������Сֵ�����Բ��˳�ʼ��Ϊ-1����Ϊ-1���żӷ����Ϊ���������һ��������Сֵʱ�Ĵ�
		��ʼ��Ϊamount+1��Ϊ����
		��ΪӲ����ֵ��С��1������ʹ��Ӳ�ҵ����������amount��amount+1һ�����Ǵ𰸣����Կ���������ʼ��

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