#pragma once
#include <vector>
#include <functional>

/*
	�����ֵ����̬�滮�ı�������٣����һ������ѭ��
	
	�ص������⣺��������Ĺ����֣������ظ����������⣬���Ա���������Ĵ𰸣�Ȼ��ֱ��ʹ��
	
	�����ӽṹ������ֽ����������Ƕ����ģ���ֵֻ��һ��Ӱ����һ�������ܻ���Ӱ��
	
	״̬ת�Ʒ��̣�������������������ϵ

	���ͣ�
		����¼�ݹ飺����ٵݹ�Ļ��������ӱ���¼���飬�������¼������������ֵ��ֱ�ӷ��أ�����������
		dp���������ݹ�תΪ��������Ȼʹ��һ�����鱣��������ֵ
*/

// ����¼�ݹ�
int question(const std::vector<int>& nums)
{
	std::vector<int> memo(nums.size(), -1);
	std::function<int(int)> dp = [&](int i)
		{
			// ��������...
			
			// �Ѿ�������������memo��ֱ�ӷ���
			if (-1 != memo[i])
			{
				return memo[i];
			}

			for (auto el : nums)
			{
				int res = dp(el);

				//... ������

				memo[el] = res;
			}

			return memo[i];
		};

	return dp(nums.size() - 1);
}

// dp������һά��ѭ����
int question(const std::vector<int>& nums)
{
	std::vector<int> dp(nums.size(), -1);

	for (int i = 0;i < nums.size();++i)
	{
		int res = -1;

		//... ������

		dp[i] = res;
	}

	return dp[nums.size() - 1];
}