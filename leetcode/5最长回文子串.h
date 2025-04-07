#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
/*
	�Ѷȣ��е�

	Ҫ�����ڵ����ַ�������Ӵ��������ͬ�ַ�Ҳ������Ӵ�
*/

/*
	������
	���������Ӵ�������Ƿ��ǻ��Ĵ�
	���������Ӵ�O(n^2)���ж��Ƿ��ǻ��Ĵ�O(n)
	�����ܵ�ʱ�临�Ӷ���O(n^3)
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
	������ɢ��
	Ҳ��labuladong�״ν���ʱʹ�õ��㷨���Ƚ����׶�
	ÿ������һ���ַ����ͳ����Ѹ��ַ�������ַ���ͬ����һ���ַ���Ϊ������������ɢ
	ֱ����������Ĵ��Ķ��壬��¼���Ļ��Ĵ�����ʼ�ͳ���

	�������ĵ�ʱ�临�Ӷ�ΪO(n)������Ĵ���ʱ�临�Ӷ�O(n)
	������ʱ�临�Ӷ���O(n^2)

	������ɢ�����������ͱ�д�ķ������������ֳ��뵽������ʱ�临�Ӷ�Ҳ���ߡ��������ͱ��У��Ա���д������̬�滮ʱʹ��
	��̬�滮Ҳֻ��O(n^2)
	����ǰ׺O(nlogn)
	��õ���Manacher��ʱ�临�Ӷ�ΪO(n)
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
	��̬�滮���о��ܸߴ��ϵ��ٶȺ��ڴ涼����������ɢ����
	�ѵ������Ƶ���������
	������һά�������á���Ϊһά���Ƶ���Ȼ�ǣ�s[0,len)��������Ӵ��ǣ�1.���s[0,len-1)��������Ӵ���ĩβ����s[len-1]== s[k],
		k �ǻ����Ӵ���ǰһ���ַ����� s[0,len)��������Ӵ��� s[k]##s[0,len-1)��������Ӵ�##s[len-1]
		���ǣ��߲�����ż�����Ĵ����������Ĵ���ǰ���ַ�����lambda���ʽ��ķ���ֵ�ܹ�����������ż����
		���ڻ��Ĵ���ȫ��һ���ַ����������aaaaaa������s[len-1]Ҳ��a����s[k]����a�����ܼ�����
		ԭ���������ķ��̲�ȷ����߽磬����ֻ�ǿ� k �ǻ����Ӵ���ǰһ���ַ� ȥ�Ƶ���
		��������ɢ�ͱ����㷨����ȷ������߽�

	��ά��������ĵķ��������Ĵ�������Ҫ�����յ�����Ҫ����ȷ��������Ҫ�ö�άdp����һ����Ŀ��Ҫ�ö�ά��һά���ڵ��۾��ܿ�������
		����dp[i][j]��ʾ��iΪ��㣬jΪ�յ���Ӵ��Ƿ��ǻ��Ĵ�
		����1.i==jʱ��true
			2.i+1==j ����s[i]==s[j],true // ��ʵҲ���Ժ�1�ϲ�����Ϊi==j��s[i]==s[j]
			3.s[i]==s[j] && dp[i+1][j-1]

		ע�⣺����dp[i][j]������dp[i+1][j-1]����ij˫ѭ��������iʱ����һѭ��i+1���л�δȷ����
		������ֵ��Ҫ���ֵ��ѭ�������ȷ������Ҫ�ı�ѭ����ʽ
		ע�⵽ij˫ѭ����Ϊ�˱��������Ӵ�����ȷ�����i�����յ�j��Ϊ��ȷ�����Ӵ��ĳ���
		��ô�Ϳ���ת��Ϊ�ȳ�����ȷ����㣬���ĳ� ki˫ѭ��,k��2~len
		������ѭ��ȷ������Ϊk����ѭ��ȷ�����Ϊi����j = i + k - 1
		����kΪ4��iΪ2���� dp[i][j] = dp[2][5]
		��ʱdp[i+1][j-1] = dp[i+1][i+k-2]= dp[3][4] = dp[3][3+2-1];//i' = 3, k' = 2
		k' < k ����ѭ����k������k'=2�������Ӵ��Ѿ�ȷ����
		����ȻҲ�������Ϊ���Ϊi����Ϊj-i+1���Ӵ����������Ϊi+1����Ϊj-i-1���Ӵ������̵��Ӵ���ȷ���������Ӵ�����ȷ����ps����仰������Ҳ��֪������

*/

string longestPalindrome3(string s)
{
	int len = s.length();
	vector<vector<bool>> dp(len, vector<bool>(len, false));
	int begin = 0, max_len = 0;
	for (int k = 1; k <= len; ++k)
	{
		for (int i = 0;i < len - k + 1;++i) // ����Ϊ1ʱi<len => ����Ϊkʱ��i<len-k+1
		{
			int j = i + k - 1;
			dp[i][j] = s[i] == s[j]; // �ַ���ȣ�������i==j
			if (k > 2) // ������ȴ���2����ȥ�����������ַ������滹��һ���Ӵ������������Ǹ��Ӵ�
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

