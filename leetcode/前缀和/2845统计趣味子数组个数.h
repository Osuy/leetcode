#pragma once
#include "../base_header.h"
/*
    难度：中等
    题目：给定一个数组，一个模数m，一个余数k
    子数组内的元素满足 el % m == k 的 个数n如果也满足 n%m==k，则称这个数组为趣味子数组
    统计数组的趣味子数组的个数

    要寻找子数组的元素满足条件的 个数，留意到元素的数组本身无关，只关心是否满足条件
    所以联想到前缀和，记录满足条件的元素个数，则presum[j]  - presum[i-1]得到[i,j]区间内的满足条件的元素的个数
    对于presum[j] 如果存在presum[i(x)-1] = presum[j] -k - m^x ，则每个i都与j构成趣味子数组
    所以需要记录下  presum % m，
    j遍历presum时，作为子数组的右界，去寻找  (presum[i] + modulo - k) % modulo 是否存在，如果存在，则答案加上其个数
    
    
    总结
        关键要素是区间，元素满足一定条件，可以联想用前缀和，求 的是子数组数量，所以hash不是保存索引而是保存出现次数
        能与j构成趣味字数的i都满足相同条件，即 (presum[j]-presum[i]) %m = k
        (presum[j] -k+m) %m = (presum[i])%ms
*/

long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) 
{
    vector<int>presum(nums.size() + 1, 0);
    for (int i = 0;i < nums.size();++i)
    {
        presum[i + 1] = presum[i] + ((k == nums[i] % modulo) ? 1 : 0);
    }

    unordered_map<int, int>map;
    long long  ans = 0;
    for (int i = 0;i < presum.size();++i)
    {
        int key = (presum[i] + modulo - k) % modulo;
        if (map.contains(key))
        {
            ans += map[key];
        }

        map[presum[i] % modulo]++;
    }

    return ans;
}

