#pragma once
#include "../base_header.h"
/*
	难度：中等
	设计一个栈，它除了栈的基本功能外，还能常数时间访问栈内最小元素

	用一个变量记录最小元素下标，入栈新元素时更新。
	但是如果最小元素出栈，就要重新定位到剩余元素里的最小元素
	所以用一个数组记录依次记录新的最小元素下标
*/

class MinStack {
public:
	vector<int> ctn;
	vector<int> min_indics;
	MinStack() {

	}

	void push(int val) {
		if (ctn.empty() || val < ctn[min_indics.back()])
		{
			min_indics.push_back(ctn.size());
		}
		ctn.push_back(val);
	}

	void pop() {
		if (min_indics.back() == ctn.size() - 1)
		{
			min_indics.pop_back();
		}
		ctn.pop_back();
	}

	int top() {
		return ctn.back();
	}

	int getMin() {
		return ctn[min_indics.back()];
	}
};