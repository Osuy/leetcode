#pragma once
#include "../base_header.h"

/*
	难度：困难
	一个大小为k的滑动窗口从数组头滑动到数组尾，每次滑动一格，求滑动期间窗口内的所有最大值

	只需关系可能成为窗口内最大元素的元素。
	例如：i目前是窗口的最大元素，那么i以前的元素无论如何都不会成为未来的最大元素，因为在i滑出之前，它们已经都滑出了
	j是窗口内的i之后的最大元素，那么i~j之间的元素也不会成为未来的最大元素
	只有i、j，以及j以后的未来第二大元素需要关注，呈现先进先出的特点，并且单调。
	于是想到单调队列，窗口右滑时右侧元素入队，把队尾小于新元素的出队，保持对内单调递减
	左侧元素如果出队的是队首，出队
*/

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	deque<int> max_indics;
	int i = 0;
	// 先将k-1个元素入队
	for (; i < k - 1;++i)
	{
		while (!max_indics.empty() && nums[max_indics.back()] < nums[i])
		{
			max_indics.pop_back();
		}
		max_indics.push_back(i);
	}

	vector<int> ans;
	for (;i < nums.size();++i)
	{
		// 每次入队维持对内单调递减
		while (!max_indics.empty() && nums[max_indics.back()] < nums[i])
		{
			max_indics.pop_back();
		}

		max_indics.push_back(i);
		// 把当前队首所指元素存入答案
		ans.push_back(nums[max_indics.front()]);

		if (i - k + 1 == max_indics.front())
		{
			max_indics.pop_front();
		}
	}

	priority_queue<vector<int>> q;
	ans.rbegin().operator*();
	return ans;
}