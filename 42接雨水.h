#pragma once
#include <vector>
using std::vector;

/*
	�Ѷȣ�����

	����ջ��ǰ��׺max
*/



/*
	����ÿһ��Ԫ�أ�����װˮ�Ķ��� = min(����ߵ����Ԫ��, ���ұߵ����Ԫ��)
	���ǿ�������������ȥ��ǰ��׺�����ֵ
	pre[i] = max(pre[i-1], el[i])
	sub[i] = max(bus[i+1], el[i])//�Ӻ���ǰ����
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

		// ��������Ҳ��ܽ���ˮ��
		for (int i = 1;i < n - 1;++i)
		{
			ans += std::max(0, std::min(pre[i], sub[i]) - height[i]);
		}
		

		return ans;
	}
};

/*
	˫ָ��
	Ҳ�൱�ڶ�ǰ��׺���ֵ���Ż�
	��Ϊǰ׺���ֵ�Ǵ�ǰ���󣬴ﵽ������������֮�󲻱�
	��׺���ֵ�ǴӺ���ǰ���ﵽ������������ֵ�󲻱�
	����ѭ������Ч�����������������ĳ���
	���ǣ������뵽������˫ָ����������ٿռ临�Ӷ�

	���ڸ����һ�������п��������ֵ�����Խ�С��һ��������
	�ߵ�ͬʱ������ߵ���С��λ�ã���˵������װˮ���ۼӵ�ans
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
	����ջ�����������
	�������ջ�ݼ����Ͳ����γɿ��Խ�ˮ�İ��ۣ�ֱ����������ջ����Ԫ��
	��ʱ��ջ��ֱ��ջ��Ԫ�ش��ڵ�����Ԫ��
		����ÿһ����ջ��Ԫ�أ����Եõ�һ������ˮ�ľ���
		���� = ����ջ���ľ���
		��߶� = min(��Ԫ�صĸ߶ȣ�ջ�׵ĸ߶�) - ���ĸ߶�
		���߶�*����ۼӵ�ans��
	��ջ��Ԫ��
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