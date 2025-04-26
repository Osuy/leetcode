#pragma once
#include "../base_header.h"
/*
	难度：中等
	给定一个只包含0和1的数组，和正整数k，代表能将多少0翻转为1
	求最大连续1的子数组

	既然可以执行至多k次翻转，意味着子数组内部最多可以有k个0
	于是题目就变成求至多含k个0的子数组的最大长度
	输入数组为10^5，且元素非负，所以考虑滑动窗口

	注意到窗口[i,j)是无需缩短的，即只允许增大。因此内循环就可以优化为内if
	右界总是右移，而右界如果遇到1且内部有k个0，则无需移动左界
*/

int longestOnes(vector<int>& nums, int k) 
{
    // 先确定初始窗口[0,r)
    int sum = 0;
    int r = 0;
    while (sum < k && r < nums.size())
    {
        sum += !!!nums[r++];
    }

    // r不断右移，l只在遇到0或者sum不为k时右移
    int l = 0;
    while (r < nums.size())
    {
        sum += !!!nums[r];
        if (!nums[r] || sum != k)
            sum -= !!!nums[l++];
        ++r;
    }

    return r - l;
}