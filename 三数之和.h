#pragma once
#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		// 经过排序后，可以使i<j<k，方便遍历
		std::sort(nums.begin(), nums.end());
		vector<vector<int>> ans;
		int size = nums.size();

		// i从0到size-3，因为需要留2个元素给j和k
		for (int i = 0; i < size - 2; ++i)
		{
			if (i > 0 && nums[i] == nums[i - 1])continue;
			if (nums[i] + nums[i + 1] + nums[i + 2] > 0)break;
			if (nums[i] + nums[size - 1] + nums[size - 2] < 0)continue;

			int key = -nums[i];
			//j与k双指针，从两端逼近，当和小于 -nums[i]时说明需要增大，于是j++
			// 当和大于与-nums[i]时，说明需要减小，于是k--
			// 相同时得到答案。题目要求不重复，所以j和k都要收拢到新的值
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
					// j和k都要收拢，而且要收拢到新的值
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