#pragma once
#include "../base_header.h"

/*
	�Ѷȣ��е�
	��������������һ���ϸ��������Ԫ�ص�Ԫ�ص�����
	ͷβԪ��ֻ���������/ǰһ������Ԫ��
	����Ԫ�ظ������

	˼·����������һ��Ԫ��num[i],���num[i]<num[i+1]��˵��i����һ���з�
	��֮��num[i]>num[i+1]��˵��iǰ��һ���з塣���ǿ����ö��ַ���С��Χ��������÷�ֵ����

	��ȫ��ͬ�Ĵ��룬�����Խ�� 862Ѱ�Ҷ���
*/

int findPeakElement(vector<int>& nums) {
	int size = nums.size();

	int l = 0, r = size - 1;

	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] > nums[mid + 1])
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}

	return l;
}