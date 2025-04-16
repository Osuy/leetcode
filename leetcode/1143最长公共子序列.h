#pragma once
#include "base_header.h"
/*
	对于 text1 的前i和字符和 text2 的前j个字符
	如果 text[i] == text2[j] 则  dp[i][j] = 1 + dp[i-1][j-1], 
	否则 dp[i][j] = dp[i-1][j-1], 
*/

int longestCommonSubsequence(string text1, string text2)
{
	int len1 = text1.length();
	int len2 = text2.length();
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

	for (int i =  1; i <= len1; ++i)
	{
		for (int j = 1; j <= len2; ++j)
		{
			if (text1[i - 1] == text2[j - 1])
			{
				dp[i][j] = 1 + dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
	}

	return dp[len1][len2];
}