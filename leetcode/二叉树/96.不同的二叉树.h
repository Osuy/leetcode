#pragma once
#include "../base_header.h"
/*
	难度：中等
	给定数字n，求由1~n构成的二叉搜索树有几种

	可以先确定根节点，然后递归地确定左子树和右子树的根节点

	由于n是最大的元素，所以只有：
		1.别的节点成为它的左子节点
		2.成为别的节点的右子节点
		3.1和2兼有

	对于1，如果知道n-1的答案Q，那么把Q的每一种可能都作为n的左子树
	对于2，让n成为Q的每一种可能里的最右节点的右节点
	对于3，把n-1分为两部分，大的那部分就是情况1，小的那部分就是情况2
		特别地，当一部分为空时，就会转化为1或2

	于是可以得出递推关系，Qn = Q0 * Qn-1 + Q1 * Qn-2 ...
	
*/

int numTrees(int lo, int hi)
{
	if (lo > hi)return 1;
	int ans = 0;
	for (int i = lo;i <= hi;++i)
	{
		ans += numTrees(lo, i - 1) * numTrees(i + 1, hi);
	}

	return ans;
}

int numTrees(int n)
{
	return numTrees(1, n);
}

int numTrees2(int n) 
{
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0;j < i;++j)
        {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }

    return dp[n];
}