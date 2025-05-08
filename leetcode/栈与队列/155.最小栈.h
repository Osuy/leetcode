#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	���һ��ջ��������ջ�Ļ��������⣬���ܳ���ʱ�����ջ����СԪ��

	��һ��������¼��СԪ���±꣬��ջ��Ԫ��ʱ���¡�
	���������СԪ�س�ջ����Ҫ���¶�λ��ʣ��Ԫ�������СԪ��
	������һ�������¼���μ�¼�µ���СԪ���±�
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