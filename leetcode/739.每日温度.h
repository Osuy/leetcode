#pragma once
#include "base_header.h"
/*
	��ÿ�����һ��������ļ��
	
	����������ÿһ�죬Ҫ��������һ�����¶ȣ���ʱ����ջ��
	�����ջ��һ�������ֵ�������ҵ��˴�
	������ջ��Ԫ�ض��ԣ��������б���С��ջ��Ԫ�صĴ�
	����Ҫ������ջֱ��ջ��Ԫ�ر����󣬻�ջ��

*/

class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& temperatures) {
		vector<int> ans(temperatures.size(), 0);

		vector<int> stack{};
		for (int i = 0;i < temperatures.size();++i)
		{
			// ջ���գ���ջ��Ԫ�ظ�С����ջ
			while (!stack.empty() && temperatures[stack.back()] < temperatures[i])
			{
				int t = stack.back();
				stack.pop_back();

				//��ǰ������ - ��ջ������ = ���������
				ans[t] = i - t;
			}

			// ����ǰ����������ջ
			stack.push_back(i);
		}

		return ans;
	}
};