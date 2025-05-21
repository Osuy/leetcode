#pragma once
#include "../base_header.h"

/*
	�Ѷȣ�����
	���һ��ջ����ÿ�γ�ջ���ǳ�ջ�������ǳ��ظ�����Ԫ��
	����ж����ͬ�ظ�������Ԫ�أ���������ջ���Ǹ�

	�������󲻳����ݽṹ�������������㷨��ʵ�ܼ�
	��Ϊ�Ѿ����߱�����ȳ������ʣ������ڲ������������һ����ջ��
	����ÿ�γ�ջ�����ظ����ε�Ԫ�أ�������ƶ��Ͱ����i��Ͱ��ʾ�����Ԫ�س�����i+1��
	���ִ�����Ȼ�������ģ�����i�ε�Ԫ�أ���Ȼ�ڵ�i����ջǰ������i-1�Σ�����Ͱ����Լ򵥵����Ϊvector
	���ִ�������Ԫ��һ�������һ��Ͱ��
	�����ͬ�ظ�������Ԫ�أ���������ջ���Ǹ�����ÿ��Ͱ���ԣ��������ջ��������Ͱ�ڵ�Ԫ��
	��ôĩβԪ�ؾ���������ջ�ģ�ֻ��ĩβpush��pop������Ͱ���Լ򵥵����Ϊvector

	����ջһ��Ԫ��ʱ������Ҫ֪�����Ѿ������˼��Σ�������hash��ά��Ԫ��-�ظ����������㳣��ʱ���ڻ�ȡ
	�ٰ��������i����Ͱ���ʾ��������i+1��
	����Ҫ�ѵ�i-1��Ͱ������Ƴ�����Ϊ�����ϳ�ջʱ����i-1��Ͱ������ͻ��Ϊ������i�ε�������ջ��Ԫ�ء�

	�� 5 7 5 7 4 5 Ϊ������ջ��
		0	5 7 4
		1	5 7
		2	5
	��ջʱ�����Ǵ����һ��Ͱȡ��ĩβԪ�أ�Ͱ�վͰ�Ͱ�Ƴ������ǵõ� 575475

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
	freqStack.push(5);//��ջΪ [5]
	freqStack.push(7);//��ջ�� [5,7]
	freqStack.push(5);//��ջ�� [5,7,5]
	freqStack.push(7);//��ջ�� [5,7,5,7]
	freqStack.push(4);//��ջ�� [5,7,5,7,4]
	freqStack.push(5);//��ջ�� [5,7,5,7,4,5]
	freqStack.pop();//���� 5 ����Ϊ 5 ����Ƶ����ߡ���ջ��� [5,7,5,7,4]��
	freqStack.pop();//���� 7 ����Ϊ 5 �� 7 ����Ƶ����ߣ���7��ӽ���������ջ��� [5,7,5,4]��
	freqStack.pop();//���� 5 ����Ϊ 5 ����Ƶ����ߡ���ջ��� [5,7,4]��
	freqStack.pop();
}
}