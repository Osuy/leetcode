#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
/*
	难度：中等

	要点在于单个字符算回文子串，多个相同字符也算回文子串
*/

/*
	暴力法
	遍历所有子串并检查是否是回文串
	遍历所有子串O(n^2)，判断是否是回文串O(n)
	所以总的时间复杂度是O(n^3)
*/

string longestPalindrome(string s)
{
	int len = s.length();
	auto is_palindrome = [&](int i, int j)->bool
		{
			while (i < j && i >= 0 && j < len && s[i] == s[j])
			{
				++i, --j;
			}
			return j <= i;
		};

	int max_len = 0;
	int begin = 0;
	for (int i = 0;i < len;++i)
	{
		for (int j = i;j < len;++j)
		{
			if (is_palindrome(i, j) && j - i + 1 > max_len)
			{
				begin = i;
				max_len = j - i + 1;
			}
		}
	}

	return s.substr(begin, max_len);
}

/*
	中心扩散法
	也是labuladong首次讲解时使用的算法，比较容易懂
	每遍历到一个字符，就尝试已该字符（或该字符相同的下一个字符）为中心向两边扩散
	直至不满足回文串的定义，记录最大的回文串的起始和长度

	遍历中心的时间复杂度为O(n)，求回文串的时间复杂度O(n)
	所以总时间复杂度是O(n^2)

	中心扩散法是易于理解和编写的方法，最容易现场想到，而且时间复杂度也不高。建议记忆和背诵，以便在写不出动态规划时使用
	动态规划也只有O(n^2)
	二分前缀O(nlogn)
	最好的是Manacher，时间复杂度为O(n)
*/

string longestPalindrome2(string s)
{
	int len = s.length();
	int begin = 0;
	int max_len = 0;
	auto find_max_palindrome = [&](int i, int j)
		{
			if (i > j)return;
			if (i < 0 || j >= len)return;
			if (s[i] != s[j])return;

			while (0 <= i && j < len && s[i] == s[j])
			{
				--i, ++j;
			}

			int len = j - i - 1;
			if (len > max_len)
			{
				begin = i + 1;
				max_len = len;
			}
		};

	for (int i = 0;i < len;++i)
	{
		find_max_palindrome(i, i);
		find_max_palindrome(i, i + 1);
	}

	return s.substr(begin, max_len);
}

/*
	动态规划（感觉很高大上但速度和内存都不如中心扩散法）
	难点在于推导联动方程
	首先是一维：不适用。因为一维的推导必然是：s[0,len)的最长回文子串是：1.如果s[0,len-1)的最长回文子串在末尾，且s[len-1]== s[k],
		k 是回文子串的前一个字符，则 s[0,len)的最长回文子串是 s[k]##s[0,len-1)的最长回文子串##s[len-1]
		但是，者并不靠偶数回文串和奇数回文串（前两种方法的lambda表达式里的返回值能够处理奇数和偶数）
		对于回文串是全是一个字符的情况，如aaaaaa，假如s[len-1]也是a，但s[k]不是a，则不能检查出。
		原因是这样的方程不确定左边界，仅仅只是考 k 是回文子串的前一个字符 去推导。
		而中心扩散和暴力算法都是确定的左边界

	二维：结合上文的分析，回文串至少需要起点和终点两个要素来确定，于是要用二维dp。（一般题目都要用二维，一维属于瞪眼就能看出来）
		假设dp[i][j]表示以i为起点，j为终点的子串是否是回文串
		则有1.i==j时，true
			2.i+1==j 且是s[i]==s[j],true // 其实也可以和1合并，因为i==j则s[i]==s[j]
			3.s[i]==s[j] && dp[i+1][j-1]

		注意：由于dp[i][j]依赖于dp[i+1][j-1]，而ij双循环遍历到i时，下一循环i+1的行还未确定。
		依赖的值在要算的值的循环后面才确定，需要改变循环方式
		注意到ij双循环是为了遍历所有子串，即确定起点i，定终点j是为了确定了子串的长度
		那么就可以转换为先长度再确定起点，下文称 ki双循环,k从2~len
		假设外循环确定长度为k，内循环确定起点为i，则j = i + k - 1
		假设k为4，i为2，则 dp[i][j] = dp[2][5]
		此时dp[i+1][j-1] = dp[i+1][i+k-2]= dp[3][4] = dp[3][3+2-1];//i' = 3, k' = 2
		k' < k 而外循环是k，所以k'=2的所有子串已经确定了
		（当然也可以理解为起点为i长度为j-i+1的子串依赖于起点为i+1长度为j-i-1的子串，即短的子串先确定，长的子串才能确定（ps：这句话不分析也能知道））

*/

string longestPalindrome3(string s)
{
	int len = s.length();
	vector<vector<bool>> dp(len, vector<bool>(len, false));
	int begin = 0, max_len = 0;
	for (int k = 1; k <= len; ++k)
	{
		for (int i = 0;i < len - k + 1;++i) // 长度为1时i<len => 长度为k时，i<len-k+1
		{
			int j = i + k - 1;
			dp[i][j] = s[i] == s[j]; // 字符相等，隐含了i==j
			if (k > 2) // 如果长度大于2，即去掉了这两个字符后里面还有一个子串，则依赖于那个子串
			{
				dp[i][j] = dp[i][j] && dp[i + 1][j - 1];
			}

			if (dp[i][j] && k > max_len)
			{
				begin = i;
				max_len = k;
			}
		}
	}

	return s.substr(begin, max_len);
}

