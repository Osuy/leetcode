#pragma once
#include "../base_header.h"
/*
	中等，但是会超时，需要利用备忘录优化，实际难度达到了困难
	判断数组能否被分为k个集合，每个集合的元素和相等

	首先，求数组的元素和能否被k整除，不能则直接false
	被整除后为average

	解法1是每层递归让元素i去放入k个sum中的任意一个。即循环里先放进0，进入下一层递归
	从下一层递归返回后，从0里出来，再放入1，进入下一层递归。。。。。
	而下一层递归是元素i+1选择放置
	该解法的缺点是必须同时存在k个sum，随着递归层次，它们会逐渐累加，直到所有sum都为average
	判断所有sum都为average是一个循环，会增加时间复杂度，导致超时
	因此重点是想到一个不需要循环就能判断答案的方式

	解法2是sum去收集元素，因为每个sum没有区别，都只要和为average。
	如果sum到达averrage，说明这个sum符合，切到下一个sum去收集
	而sum1收集的元素，要用一个used数组去标记已使用
	sum2就不能再收集了
	这样当递归到达sumk收集完成时，也就说明找答案
	而假如循环结束，则说明目前的收集组合不能找到答案，返回上一层，下一个循环继续找

	但是依然会超时
	这是因为假如sum1 收集了1和4，sum2收集了2和3，但是没找到答案
	于是退回到第一层，继续循环，sum1收集了2和3，sum2收集了1和4
	显然这种组合已经发生过，也不会有正确答案，不必浪费时间继续
	而used记录着收集过的组合。可以再把used和用hash表保存起来
	如果递归时，发现hash表保存过used，并且used的值为false，则说明当前used找不到答案，直接返回

*/

bool canPartitionKSubsets(vector<int>& nums, int k) {
	int average = 0;
	for (auto el : nums)average += el;
	if (average % k)return false;
	average /= k;
	bool found = false;

	// 解法1，元素找桶，判断成功复杂，会超时
	// vector<int> sum(k, 0);
	// auto dfs = [&](this auto&& dfs, int i)->void
	// {
	//     if(found)return;
	//     if(i==nums.size())
	//     {
	//         for(int index = 0; index < k; ++index)
	//         {
	//             if(sum[index] != average)
	//                 return;
	//         }
	//         found = true;
	//         return;
	//     }

	//     for(int index = 0;index < k; ++index)
	//     {
	//         if(sum[index] + nums[i] > average)continue;

	//         sum[index] += nums[i];
	//         dfs(i+1);
	//         sum[index] -= nums[i];
	//     }
	// };

	// dfs(0);

	// return found;

	unsigned short used = 0;
	unordered_map<unsigned short, bool> useds; // 保存已经收集过的used组合
	auto dfs = [&](this auto&& dfs, int bucket, int i, int start)->bool
		{
			// 剩下0个桶，说明成功
			if (i == 0)
			{
				return true;
			}

			// 该桶已经符合，继续递归下一个桶
			if (bucket == average)
			{
				useds[used] = dfs(0, i - 1, 0);

				return useds[used];
			}

			// 如果used曾使用过，直接返回保存的结果
			if (useds.contains(used))
			{
				return useds[used];
			}

			// 循环，选择一个元素放入桶内，进入下一层递归
			for (int index = start; index < nums.size(); ++index)
			{
				// 跳过已用的元素和相加后会超出平均值的元素
				if (used & (1 << index))continue;
				if (bucket + nums[index] > average)continue;

				bucket += nums[index];
				used |= (1 << index);
				
				if (dfs(bucket, i, index + 1))return true;
				
				used ^= (1 << index);
				bucket -= nums[index];
			}

			return false;
		};

	return dfs(0, k, 0);
}