#pragma once
#include "../base_header.h"
/*
	难度：困难
	一个数组，表示每个人的身高，假如两个人中间不存在比两人任意一人高的人，则认为前者可以看到后者
	也即：对于每个人，他可以看到他身后至多不高于他、且不被挡住的人
	求每个人可以看到的人的数量

	显然，为了能被i看到，j需要两个条件：
		1.不被(i,j)之间的人挡住，即他要这些人的人高
		2.要比i矮

	1.说明了要使用单调栈维护一个递增栈，
	2.说明了栈内并不是所有人都能被i看见，第二个比i高的人就看不见了

	由于i也要入栈，恰好i入栈要把比他矮的人出战以维持栈的单调递增
	于是出栈了几个人，i就能看到这些人。另外第一个比i高的也是能看见的
	于是
*/

vector<int> canSeePersonsCount(vector<int>& heights) {
	int n = heights.size();
	vector<int> res(n);
	vector<int> s;
	for (int i = n - 1; i >= 0; i--) {
		int k = 0;
		while (!s.empty() && s.back() <= heights[i]) {
			// k记录几个人被出栈了，这些人也都是能被i看到的
			k++;
			s.pop_back();
		}
		res[i] = k + (s.empty() ? 0 : 1);// 如果栈非空，那么栈顶也是能被看到的
		// nums[i] 身后的更大元素
		s.push_back(heights[i]);
	}
	return res;
}