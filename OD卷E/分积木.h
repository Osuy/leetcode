#pragma once
#include <vector>
#include <iostream>
#include <numeric>

/*
	�������Ϊ����
	ÿ���������ͬ����������һ�龡���ܴ�

	��Ϊÿ���������ͬ��������������;���0�����������������Ϊ0

	����ȡ����һһ������ʣ�µ�Ԫ�ص�������������
*/

void q5()
{
	int n = 0;
	std::cin >> n;

	int xor_sum = 0;
	std::vector<int> vec(n, 0);
	for (auto& el : vec)
	{
		std::cin >> el;
		xor_sum ^= el;
	}

	if (0 != xor_sum)
	{
		std::cout << "NO" << std::endl;
	}

	std::cout << std::accumulate(vec.begin(), vec.end(), 0) - *std::min_element(vec.begin(), vec.end()) << std::endl;

}

