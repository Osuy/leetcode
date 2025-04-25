#pragma once
#include "../base_header.h"
/*
	难度：中等
	求数组的最长子数组，且该子数组内大于8的元素比小于等于8的元素更多

	思路：首先要注意到只需关系元素是否大于8而不必关系元素本身的值
	所以可以把元素看作是1（大于8）和-1（小于等于8）然后求解最长的子数组，且子数组的和大于0
	那么区间、求和，元素可能为负，就容易联想到用前缀和+哈希表
	和大于0，意味着presum[i] > presum[j]
	由于presum[0] = 0所以对于任意的presum[i]>0时，[0, i]满足条件
	presum[i]<=0时，要去寻找最远的j。注意是找最远的而不是最小的，可以不用循环去找
	因为每个元素累加到前缀和上都只有1或-1，所以如果对于 presum[i]
	在[0,i-1]的范围内一定存在j， presum[j] = presum[i]-1（拉格朗日定理）
	所以只需要去找 presum[i]-1 是否存在即可，通过提前将所有presum存放到哈希表，可快速判断
*/

int longestWPI(vector<int>& hours) {
	vector<int> presum(hours.size() + 1, 0);
	for (int i = 0;i < hours.size();++i)
	{
		presum[i + 1] = (hours[i] > 8 ? 1 : -1) + presum[i];
	}

	int ans = 0;
	unordered_map<int, int> map;
	for (int i = 0;i < presum.size();++i)
	{
		if (!map.contains(presum[i]))
		{
			map[presum[i]] = i;
		}
		// 如果是求区间和为0，应该在这里加个else来求
		// 但是本题求的是区间和大于0，要找map[presum[i]-1]，和这个if是无关的
		// 所以写在同一个作用域内

		if (presum[i] > 0)
		{
			ans = max(ans, i);
		}
		else if (map.contains(presum[i] - 1))
		{
			ans = max(ans, i - map[presum[i] - 1]);
		}
	}
	return ans;
}
/*
	解法二：单调栈
	注意到对于i，要去找最远的j，且presum[i] > presum[j]
	若从0开始找，遇到大于自己的跳过，遇到小于自己的就是最远的。
	因此可以维护一个单调递减的栈。
	注意如果i的右边存在k，presum[k] > presum[i]
	那么[j,k]区间一定满足，且比[j,i]更长。因此不能从左往右遍历i，而要逆向遍历

*/
int longestWPI2(vector<int>& hours) {
	vector<int> presum(hours.size() + 1, 0);
	vector<int> st;
	st.push_back(0);
	for (int i = 0; i < hours.size(); ++i)
	{
		presum[i + 1] = (hours[i] > 8 ? 1 : -1) + presum[i];
		if (presum[i + 1] < presum[st.back()])
		{
			st.push_back(i+1);
		}
	}

	int ans = 0;
	for (int i = presum.size()-1;i>=0;--i)
	{
		while (!st.empty() && presum[i] > presum[st.back()])
		{
			ans = max(ans, i - st.back());
			st.pop_back();
		}
	}

	return ans;
}