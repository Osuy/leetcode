#pragma once
#include "../base_header.h"
/*
	켜똑：위켜
*/

bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
	multiset<int> numset;
	int l = 0, r = 0;
	deque<set<int>::iterator> its;
	while (r < nums.size())
	{
		auto n = nums[r++];
		auto lit = numset.lower_bound(n - valueDiff);
		auto rit = numset.lower_bound(n + valueDiff);
		if (rit != numset.end())++rit;
		for (auto it = lit;it != rit;++it)
		{
			if (abs(n - *it) <= valueDiff)
			{
				return true;
			}
		}

		its.push_back(numset.insert(n));

		if (numset.size() > indexDiff)
		{
			numset.erase(its.front());
			its.pop_front();
			++l;
		}
	}

	return false;
}