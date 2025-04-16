#pragma once
#include "base_header.h"
/*
	求每天的下一更大问题的间隔
	
	分析：对于每一天，要找它的下一更大温度，暂时存入栈中
	如果入栈了一个更大的值，则它找到了答案
	对于入栈的元素而言，它是所有比他小的栈内元素的答案
	所以要持续出栈直到栈内元素比它大，或栈空

*/

class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& temperatures) {
		vector<int> ans(temperatures.size(), 0);

		vector<int> stack{};
		for (int i = 0;i < temperatures.size();++i)
		{
			// 栈不空，且栈顶元素更小，出栈
			while (!stack.empty() && temperatures[stack.back()] < temperatures[i])
			{
				int t = stack.back();
				stack.pop_back();

				//当前的天数 - 出栈的天数 = 间隔的天数
				ans[t] = i - t;
			}

			// 将当前的天数存入栈
			stack.push_back(i);
		}

		return ans;
	}
};