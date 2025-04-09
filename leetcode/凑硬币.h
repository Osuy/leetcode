#pragma once
#include <vector>
using std::vector;

/*

  0 1 2 3 4 5 6 7 8 9 10 11
2   0 1 
    0 0 0 0 0 0 0 0 0  0  0
1   1 2 3 4 5 6 7 8 9 10 11
2   1 1 2 2 3 3 4 4 5  5  6
5   1 1 2 2 1 2 2 3 3  2  3
*/
int coinChange(vector<int>& coins, int amount) {
    int size = coins.size();
    vector<vector<int>> dp(amount + 1, vector<int>(size, INT_MAX));
    for (int i = 0; i < size; ++i)
    {
        dp[coins[i]][i] = 1;
    }

    for (int j = 1; j <= amount; ++j)
    {
        for (int i = 0;i < size;++i)
        {
            if (coins[i] < j)
            {
				if (0 < i && dp[j][i - 1] < dp[j - coins[i]][i])
				{
					dp[j][i] = dp[j][i - 1];
				}
				else
				{
					dp[j][i] = 1 + dp[j - coins[i]][i];
				}
            }
            else if (coins[i] > j)
            {
                dp[j][i] = dp[j][i - 1];
            }
        }
    }

    return dp[amount][size-1] == INT_MAX ? -1 : dp[amount][size - 1];
}