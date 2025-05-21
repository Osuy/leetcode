#pragma once
#include "../../base_header.h"
/*
	�Ѷȣ��е�
	������������������������ʹ�����������������������������С����

	����ջ�ⷨ��
	�������ά������ջ����ջ��Ԫ��������Ԫ�أ�������ǰ�ľ�������������������
	�������ά���ݼ�ջ���������ľ�������������ҽ�
*/
int findUnsortedSubarray(vector<int>& nums) 
{
	int n = nums.size();
	int left = INT_MAX, right = INT_MIN;
	// ����ջ���洢Ԫ������
	stack<int> incrStk;
	for (int i = 0; i < n; i++) 
	{
		while (!incrStk.empty() && nums[incrStk.top()] > nums[i]) 
		{
			// ������Ԫ�ض�������Ԫ�أ�������С�����������������������߽�
			left = min(left, incrStk.top());
			incrStk.pop();
		}
		incrStk.push(i);
	}
	// �ݼ�ջ���洢Ԫ������
	stack<int> decrStk;
	for (int i = n - 1; i >= 0; i--) 
	{
		while (!decrStk.empty() && nums[decrStk.top()] < nums[i]) 
		{
			// ������Ԫ�ض�������Ԫ�أ�����������������������������ұ߽�
			right = max(right, decrStk.top());
			decrStk.pop();
		}
		decrStk.push(i);
	}
	if (left == INT_MAX && right == INT_MIN) 
	{
		// ˵������ջû�е����κ�Ԫ�أ��� nums �������������
		return 0;
	}
	return right - left + 1;
}

/*
	ǰ׺���ֵ�ⷨ
	һ���������� ��ǰ׺���ֵ�ͺ�׺��Сֵ����ȵ�
	������һ���������飬����ǰ׺���ֵ�ͺ�׺��Сֵ�� ��һ���Լ����һ����ͬ��Ԫ�ع��ɵ�����
	������������
*/
int findUnsortedSubarray(vector<int>& nums) 
{

	auto premax = nums, postmin = nums;
	for (int i = 1;i < nums.size();++i)
	{
		premax[i] = max(premax[i - 1], premax[i]);
	}

	for (int i = nums.size() - 2;i >= 0;--i)
	{
		postmin[i] = min(postmin[i + 1], postmin[i]);
	}

	int l = 0, r = nums.size() - 1;
	while (l < nums.size() && premax[l] == postmin[l])++l;
	while (r >= l && premax[r] == postmin[r])--r;

	return  r - l + 1;

}