#pragma once
#include "../base_header.h"
/*
	难度：困难

	求字符串s的子序列里出现字符串t的次数
	对于字符串s的前i个字符的子序列里，包含t的前j个字符
	假如s[i] != s[j]，则说明s[i]不能包含在子序列中，所以有i没i都一样
	答案是s的前i-1个字符的子序列里，出现t的前j个字符的子串的次数
	而如果s[i] == s[j]，则i可以包含在子序列里，也可以不包含
	如果包含，则相当于子序列的最后一个字符必须是s[i]，并且t的前j个字符的子串末尾也等于s[i]
	所以将二者消除，可以得到s的前i-1个字符的子序列里，出现t的前j-1个字符的子串的次数

	最后把包含和不包含的答案相加

	例子
		abcd 的子序列里包含bd的次数，为1
		此时再s末尾假设一个e，abcde的子序列里出现bd的次数，显然还是1
		因为e!=d，包含了e的子序列，e一定是末尾，而e！= d
		所以bd无法匹配包含了e的子序列，只能从不包含e的子序列匹配
		所以有e没有e都一样

		然后在t的末尾加一个e，abcde的子序列里出现bde的次数，是1，但是其中有一次运算
		由于s和t的末尾都是e，所以答案里肯定包含了“abcd 的子序列里包含bd的次数”，就是1
		此外，答案还包含了“abcd的子序列里bde的次数”不过是0，所以1+0 = 1

	不能使用dp优化
	因为dp[i][j] 依赖于dp[i-1][j-1]
	如果优化为一维数组，则dp[i-1][j-1]会被dp[i-1][j]覆盖
*/

int numDistinct(string s, string t) {
    int slen = s.length(), tlen = t.length();
    vector<unsigned long long> base(tlen + 1, 0);
    base[0] = 1;
    vector<vector<unsigned long long>> dp(slen + 1, base);
    for (int i = 0; i < slen; i++)
    {
        for (int j = 0; j < min(tlen, i + 1); ++j) // j比i大的情况无需遍历
        {
            dp[i + 1][j + 1] = dp[i][j + 1]; // 答案肯定有 不包含s[i]的子序列里出现。。。。的次数
            if (s[i] == t[j])
            {
                dp[i + 1][j + 1] += dp[i][j];// 如果s[i] == t[j]则答案也还有 包含s[i]的子序列里出现。。。。的次数
            }
        }
    }

    return dp.back().back();
}