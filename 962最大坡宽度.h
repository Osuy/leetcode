#pragma once
/*
	�Ѷ��е�

	�������飬������ el[i]<=el[j],i<j ��j-i�����ֵ

	��j-i�����߶�������������������el[i]<=el[j]��

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