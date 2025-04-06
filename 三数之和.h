#pragma once
#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		// ��������󣬿���ʹi<j<k���������
		std::sort(nums.begin(), nums.end());
		vector<vector<int>> ans;
		int size = nums.size();

		// i��0��size-3����Ϊ��Ҫ��2��Ԫ�ظ�j��k
		for (int i = 0; i < size - 2; ++i)
		{
			if (i > 0 && nums[i] == nums[i - 1])continue;
			if (nums[i] + nums[i + 1] + nums[i + 2] > 0)break;
			if (nums[i] + nums[size - 1] + nums[size - 2] < 0)continue;

			int key = -nums[i];
			//j��k˫ָ�룬�����˱ƽ�������С�� -nums[i]ʱ˵����Ҫ��������j++
			// ���ʹ�����-nums[i]ʱ��˵����Ҫ��С������k--
			// ��ͬʱ�õ��𰸡���ĿҪ���ظ�������j��k��Ҫ��£���µ�ֵ
			int j = i + 1, k = size - 1;
			while (j < k)
			{
				if (nums[j] + nums[k] < key)
				{
					j++;
				}
				else if (nums[j] + nums[k] > key)
				{
					k--;
				}
				else
				{
					ans.push_back({ nums[i], nums[j], nums[k] });
					// j��k��Ҫ��£������Ҫ��£���µ�ֵ
					++j;
					while (j < k && nums[j] == nums[j - 1])++j;
					--k;
					while (j < k && nums[k] == nums[k + 1])--k;
				}
			}
		}
		return ans;
	}
};