#pragma once
#include "../base_header.h"
/*
	难度：中等
	给出一个字符串表示的非负整数，从中移出k个数字，使剩余的数字最小
	返回最小数字的 字符串，不包含前导0

	如果要使数字尽可能小，首先考虑i和i+1，如果i更大，则必然移出i
	因为i+1顶替i一定会更小
	而如果i+1更大，不一定要移出i+1，因为后面可能存在更大的值
	于是可以维护一个ans字符串遍历数字符串，遇到的新元素如果比ans的尾部小
	则循环移除尾部元素，直到新元素比尾部大，遇到的新元素比ans尾部大，则直接加入
	于是ans维持单调递增

	但是只允许移出k个数字，于是从ans尾部移除的操作只能执行k次
	由于不能包含先导0，于是加入ans的操作必须是新元素非0或ans非空

	最后可能遍历完所有字符，还没有移除k个的情况
	此时ans是单调递增的，只需从尾部移除剩余次数个字符即可
*/

string removeKdigits(string num, int k) {
	string ans;
	for (auto c : num)
	{
		// 至多pop k次，
		while (k > 0 && !ans.empty() && c < ans.back())
		{
			k--;
			ans.pop_back();
		}

		// 当ans为空时，先导0直接跳过。也不需计入到k次操作中
		if (ans.empty() && c == '0')continue;
		
		ans.push_back(c);
	}

	// 未移除k个，从尾部移除剩余次数个字符
	while (!ans.empty() && k-- > 0)
	{
		ans.pop_back();
	}

	return ans.empty() ? "0" : ans;
}