#pragma once
#include <vector>
using std::vector;

/*
	难度：困难

	单调栈，前后缀max
*/



/*
	对于每一个元素，其能装水的多少 = min(它左边的最大元素, 它右边的最大元素)
	于是可以用两个数组去求前后缀的最大值
	pre[i] = max(pre[i-1], el[i])
	sub[i] = max(bus[i+1], el[i])//从后往前遍历
*/

class Solution {
public:
	int trap(vector<int>& height)
	{
		int n = height.size();
		int ans = 0;

		vector<int> pre(n, 0);
		pre[0] = height[0];
		for (int i = 1;i < n;++i)
		{
			pre[i] = std::max(pre[i - 1], height[i]);
		}

		vector<int> sub(n, 0);
		sub[n-1] = height[n-1];
		for (int i = n - 2;i >= 0;--i)
		{
			sub[i] = std::max(sub[i + 1], height[i]);
		}

		// 最左和最右不能接雨水，
		for (int i = 1;i < n - 1;++i)
		{
			ans += std::max(0, std::min(pre[i], sub[i]) - height[i]);
		}
		

		return ans;
	}
};

/*
	双指针
	也相当于对前后缀最大值的优化
	因为前缀最大值是从前往后，达到整个数组的最大之后不变
	后缀最大值是从后往前，达到整个数组的最大值后不变
	两个循环的有效长度相加是整个数组的长度
	于是，容易想到可以用双指针替代，减少空间复杂度

	对于更大的一方，它有可能是最大值，所以较小的一方继续走
	走的同时，如果走到更小的位置，则说明可以装水，累加到ans
*/
class Solution2 {
public:
	int trap(vector<int>& height)
	{
		int ans = 0;
		int n = height.size();
		int left = 0;
		int right = n - 1;

		int premax = height[0];
		int submax = height[n - 1];
		while (left <= right)
		{
			if (premax < submax)
			{
				premax = std::max(premax, height[left]);
				ans += std::max(0, premax - height[left]);
			}
			else
			{
				submax = std::max(submax, height[right]);
				ans += std::max(0, submax - height[left]);
			}
		}

		return ans;
	}
};

/*
	单调栈法，不易理解
	如果保持栈递减，就不会形成可以接水的凹槽，直到遇到大于栈顶的元素
	此时出栈，直至栈顶元素大于等于新元素
		对于每一个出栈的元素，可以得到一个容纳水的矩形
		其宽度 = 它与栈顶的距离
		其高度 = min(新元素的高度，栈底的高度) - 它的高度
		将高度*宽度累加到ans里
	入栈新元素
*/
class Solution3 {
public:
	int trap(vector<int>& height)
	{
		vector<int> st{};
		int ans = 0;

		for (int i = 0; i < height.size(); ++i)
		{
			while (!st.empty() && height[st.back()] < height[i])
			{
				int n = st.back();
				st.pop_back();

				if (0 < st.size())
				{
					ans += (std::min(height[i], height[st.front()]) - height[n]) * (n - st.back());
				}
			}

			st.push_back(i);
		}

		return ans;
	}
};