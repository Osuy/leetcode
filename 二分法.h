#pragma once
#include "leetcode/base_header.h"

// ��׼�Ķ��ַ����
int binary_search(const vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size();
	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (nums[mid] < target)
		{
			l = mid + 1;
		}
		else if (nums[mid] > target)
		{
			r = mid;
		}
		else
		{
			return mid; // ע��˴�����return l
		}
	}

	return l;
}

/*
	��ʱwhile (l < r)����ʱwhile (l <= r)��
		ȡ����ʹ�ú������䣬r = nums.size()������ r = nums.size() - 1
		while�������ж������ڻ�����Ԫ�صģ������ǰ�պ����䣬l < r��ʾ���������ڻ���Ԫ��
		�����ǰ�պ�����䣬l<=r��ʾ�����ڻ���Ԫ��
		ͬ�� r = mid ���� r = mid-1 Ҳ���������

		����ʹ��ǰ�պ󿪣�������Ŀ����Ҫǰ�պ��
*/

/* 
	Ѱ����߽磨��һ����С��target���Ŀ��
	��Ҫ������ nums[mid] == target ʱ��ҲҪ�����ҽ�
	��Ϊmid���������߶����ܴ����ظ�Ԫ�أ��������ҵ������
	���Բ�С��ʱ�������ҽ�
	�ھ�������粻ͣ���ҽ�
 */
int lower_bound(const vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size();
	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (nums[mid] < target)
		{
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}

	return l;
}

/*
	Ѱ���ұ߽����һ��Ԫ�أ���һ������target���Ŀ��
	nums[mid] == target ʱ��ҲҪ�������
	ע�⣺���ص����ұ߽����һ��Ԫ�� / ��һ���ϸ����target��Ԫ��
	�������Ҫ�б߽磬�����1
 */
int higher_bound(const vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size();
	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (nums[mid] > target)
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

/*
	���ַ������÷�Χ
	1.���������
	2.����������ϵ�ķ��̣��𰸹���ĳ���Ա����ʵ�����ϵ��������Ա������������ȷ��
	
	��������Ŀ����
	1.���Ҷ�ֵ
	2.�ڵ�����ϵ�������ұ߽�
*/