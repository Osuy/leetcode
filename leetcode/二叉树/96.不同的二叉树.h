#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	��������n������1~n���ɵĶ����������м���

	������ȷ�����ڵ㣬Ȼ��ݹ��ȷ�����������������ĸ��ڵ�

	����n������Ԫ�أ�����ֻ�У�
		1.��Ľڵ��Ϊ�������ӽڵ�
		2.��Ϊ��Ľڵ�����ӽڵ�
		3.1��2����

	����1�����֪��n-1�Ĵ�Q����ô��Q��ÿһ�ֿ��ܶ���Ϊn��������
	����2����n��ΪQ��ÿһ�ֿ���������ҽڵ���ҽڵ�
	����3����n-1��Ϊ�����֣�����ǲ��־������1��С���ǲ��־������2
		�ر�أ���һ����Ϊ��ʱ���ͻ�ת��Ϊ1��2

	���ǿ��Եó����ƹ�ϵ��Qn = Q0 * Qn-1 + Q1 * Qn-2 ...
	
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