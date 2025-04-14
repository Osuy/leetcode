#pragma once
#include "base_header.h"

/*
	�Ѷȣ��е�
	���ͣ����ֲ���
	��Ŀ��
		����һ�������� hour ����ʾ�㵽��칫�ҿ��õ���ͨ��ʱ�䡣Ҫ����칫�ң�����밴����������� n ���г��������һ������Ϊ n ���������� dist ������ dist[i] ��ʾ�� i ���г�����ʻ���루��λ��ǧ�ף���
		ÿ���г���ֻ�������㷢���������������Ҫ�������г�֮��ȴ�һ��ʱ�䡣
		���磬�� 1 ���г���Ҫ 1.5 Сʱ����������ٵȴ� 0.5 Сʱ������ڵ� 2 Сʱ�����ĵ� 2 ���г���
		��������������ʱ��ǰ����칫����Ҫ��ȫ���г��� ��С������ ʱ�٣���λ��ǧ��ÿСʱ��������޷�׼ʱ����򷵻� -1 ��

		���ɵĲ���������֤�𰸲����� 107 ���� hour �� С�������������λ���֡�
*/

class Solution
{
public:
	// dist ���� speed �Ļ���ʱ��
	double use_time(span<int> dists, int speed)const
	{
		double res = 0.0;
		for (int i = 0;i < dists.size() - 1;++i)
		{
			res += ceil((double)dists[i] / speed);
		}

		return res + ceil((double)dists.back() / speed);
	}
	
	int minSpeedOnTime(span<int> dists, double hour)
	{
		if (ceil(hour) < dists.size())
		{
			return -1;
		}

		// ���ֲ��ҷ���������Ŀ���Ҫ���趨�����С�߽�
		// �����ƽ��ֵ���㣬���Ը�С��ֵ
		// �����ƽ��ֵ�����㣬���Ը����ֵ
		// ֪�����ұ߽��غϣ���Ϊ�����������Բ�1ҲҪ�˳�ѭ����
		int l = 1;
		int r = 1e7 + 1;
		while (l < r)
		{
			double ut = use_time(dists, (l + r) >> 1);
			if (ut < hour)
			{
				r = (l + r) >> 1;
			}
			else
			{
				l = 1 + ((l + r) >> 1);
			}
		}
	}
};