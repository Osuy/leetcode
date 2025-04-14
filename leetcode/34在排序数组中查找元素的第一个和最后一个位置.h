#pragma once
#include "base_header.h"
/*
	�Ѷȣ��е�
	���ͣ����ֲ���
	��Ŀ������
		����һ�����շǵݼ�˳�����е��������� nums ����һ��Ŀ��ֵ target�������ҳ�����Ŀ��ֵ�������еĿ�ʼλ�úͽ���λ�á�
		��������в�����Ŀ��ֵ target ������ [-1, -1]��
		�������Ʋ�ʵ��ʱ�临�Ӷ�Ϊ O(log n) ���㷨��������⡣

	���������ζ��ֲ��ҷֱ��ҳ�����
*/

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) 
	{
		// ����ա���������ֵС��taget���������Сֵ����target����������������return
		if (nums.empty() || target < nums.front() || nums.back() < target)
		{
			return { -1, -1 };
		}

		int l = 0;
		int r = nums.size() - 1;

		int res_r = (l + r) >> 1;
		while (l < r)
		{
			if (nums[res_r] <= target)
			{
				l = res_r;
				res_r = ((1 + l + r) >> 1);
			}
			else
			{
				r = res_r - 1;
				res_r = (l + r) >> 1;
			}
		}

		l = 0;
		r = res_r;
		int res_l = (l + r) >> 1;
		while (l < r)
		{
			if (target <= nums[res_l])
			{
				r = res_l;
				res_l = ((l + r) >> 1);
			}
			else
			{
				l = res_l + 1;
				res_l = (l + r) >> 1;
			}
		}

		if (target == nums[res_l] && target == nums[res_r])
		{
			return { res_l, res_r };
		}

		return { -1, -1 };
	}
};