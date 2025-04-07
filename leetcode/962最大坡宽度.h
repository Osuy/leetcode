#pragma once
/*
	难度中等

	对于数组，求满足 el[i]<=el[j],i<j 的j-i的最大值

	求j-i，二者都是索引，限制条件是el[i]<=el[j]，

	 vector<int> st{ 0 };
		for(int i=1;i<nums.size();++i)
		{
			if(nums[i]<nums[0])
			{
				st.push_back(i);
			}
		}

		while(!st.empty())
		{
			if(nums[st.back()] <= nums.back())
			{
				ans = max(ans, nums.size()-st.back());
				st.pop_back();
			}
		}
		return ans;
*/