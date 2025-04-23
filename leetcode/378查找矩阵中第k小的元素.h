#pragma once
#include "base_header.h"
/*
	�Ѷ��е�
	����ÿ��ÿ�ж����ǵݼ��������kС��Ԫ��

	����һ��ֱ������
	��������������+ȥ��
		��ʼ�����Ͻ���ѣ�Ȼ��ѭ�����ѣ������ұߺ��±ߵ�Ԫ����ѣ����ܴ����ظ�������Ҫ�ù�ϣ��ȥ��
		����k�εõ���
		��ѭ��k�Σ��������swimҪС�� logk�Σ�������ʱ�临�Ӷ�OС��(klogk)

	�����������ֲ���
		��Ȼ���ڷǵݼ�����Ҫ���뵽���ֲ��ҡ���kС��Ԫ��һ���ھ�������Ͻ�
		������һ������������Ͻǡ�����ͨ��С��ĳֵ��ȡһ�����Ͻǣ������ȡ��һ���Ԫ�أ�Ч�ʸ�
		��˸�ֵ������mid (min + max)/2���õ���
		�����Ͻǵ�Ԫ������С��k��˵��midС�ڴ𰸣�����mid = (mid+right)/2�ڴμ������Ͻǵ�����
		ֱ�����Ͻ�ǡ��Ϊk����ʱright ��Ϊ��

		ͳ�����Ͻ�Ԫ�ظ����ķ������Ӷ���o(max(row, col))�����ֲ��ҵ�ȷ��midʱ�临�Ӷ���O(log(row*col))
		�����ܸ��Ӷ�ΪO(max(row, col) * log(row*col))�������ȶ�������죬����Ϊһ�ֶ�ά���ֲ��ҵ�˼·���Լ���
*/

int kthSmallest(vector<vector<int>>& matrix, int k)
{
	// ����С��N��Ԫ�ص�����
	auto count_smaller_than_or_equal_N = [&matrix](int N)
	{
		int i = matrix.size() - 1;
		int j = 0;
		int count = 0;
		// �����½ǿ�ʼ�����<=N��õ����ϵĶ�<=N���ۼӵ�count��ȥ��һ��
		// ��������
		while (j < matrix[0].size() && i >= 0)
		{
			if (matrix[i][j] <= N)
			{
				count += i + 1;
				++j;
			}
			else
			{
				--i;
			}
		}

		return count;
	};

	int left = matrix[0][0];
	int right = matrix.back().back();
	while (left < right)
	{
		int mid = (left + right) >> 1;
		int count = count_smaller_than_or_equal_N(mid);
		if (count < k)
		{
			left = mid + 1;
		}
		else
		{
			right = mid;
		}
	}

	return right;
}