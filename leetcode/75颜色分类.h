#pragma once
#include "base_header.h"

/*
	难度：中等
	对只含有0、1、2三种元素的数组排序，不使用sort，仅一次遍历

	思路：和“删除重复元素” 、“移动零”一样，维护一个slow指针维护有效区间，fast指针负责遍历
	当遇到有效元素，则swap该元素和有效区间的下一个元素
	区别在于存在三种元素，因此可以在数组尾部维护2的有效区间，头部和上文一样维护0的有效区间
	中间的无效区间在互换后，自然只剩下1
	注意：与0区间互换，i正常++，但是与2区间互换时，i保持不动
	因为和2区间的前一个元素互换后，i所指的元素依然属于无效区间
*/

void sortColors(vector<int>& nums) {
	int l = 0, r = nums.size() - 1;
	for (int i = 0;i <= r;++i)
	{
		if (0 == nums[i])
		{
			std::swap(nums[l++], nums[i]);
		}
		else if (2 == nums[i])
		{
			std::swap(nums[r--], nums[i--]);// 与2区间的前一个元素互换，i需要--，然后循环体++，使其保持不动
		}
	}
	string str;
	str.erase()
}