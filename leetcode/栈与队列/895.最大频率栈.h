#pragma once
#include "../base_header.h"

/*
	难度：困难
	设计一个栈，它每次出栈不是出栈顶，而是出重复最多的元素
	如果有多个相同重复次数的元素，出最晚入栈的那个

	此题想象不出数据结构就做出不来，算法其实很简单
	因为已经不具备后进先出的性质，所以内部不必再真的有一个“栈”
	由于每次出栈都出重复最多次的元素，可以设计多个桶，第i个桶表示里面的元素出现了i+1次
	出现次数必然是连续的，出现i次的元素，必然在第i次入栈前出现了i-1次，所以桶组可以简单地设计为vector
	出现次数最多的元素一定在最后一个桶里
	多个相同重复次数的元素，出最晚入栈的那个。对每个桶而言，如果按入栈次数排列桶内的元素
	那么末尾元素就是最晚入栈的，只对末尾push和pop，于是桶可以简单地设计为vector

	当入栈一个元素时，首先要知道它已经出现了几次，可以用hash表维护元素-重复次数，方便常数时间内获取
	再把它放入第i个的桶里，表示它出现了i+1次
	不需要把第i-1个桶里的它移除，因为当不断出栈时，第i-1个桶里的它就会成为“出现i次的最晚入栈的元素”

	以 5 7 5 7 4 5 为例，入栈后：
		0	5 7 4
		1	5 7
		2	5
	出栈时，总是从最后一个桶取出末尾元素，桶空就把桶移除，于是得到 575475

*/
namespace q895
{

class FreqStack {
public:

	vector<vector<int>> freqToValue;
	unordered_map<int, int> freq;
	vector<int> st;
	FreqStack()
	{
	}

	void push(int val)
	{
		freq[val]++;
		if (freqToValue.size() < freq[val])
		{
			freqToValue.emplace_back();
		}
		freqToValue[freq[val] - 1].push_back(val);
		st.push_back(val);
	}

	int pop()
	{
		int ans = freqToValue.back().back();
		freqToValue.back().pop_back();
		if (freqToValue.back().empty())
		{
			freqToValue.pop_back();
		}
		freq[ans]--;

		return ans;
	}
};

void test()
{
	FreqStack freqStack{};
	freqStack.push(5);//堆栈为 [5]
	freqStack.push(7);//堆栈是 [5,7]
	freqStack.push(5);//堆栈是 [5,7,5]
	freqStack.push(7);//堆栈是 [5,7,5,7]
	freqStack.push(4);//堆栈是 [5,7,5,7,4]
	freqStack.push(5);//堆栈是 [5,7,5,7,4,5]
	freqStack.pop();//返回 5 ，因为 5 出现频率最高。堆栈变成 [5,7,5,7,4]。
	freqStack.pop();//返回 7 ，因为 5 和 7 出现频率最高，但7最接近顶部。堆栈变成 [5,7,5,4]。
	freqStack.pop();//返回 5 ，因为 5 出现频率最高。堆栈变成 [5,7,4]。
	freqStack.pop();
}
}