#pragma once
#include <vector>
#include <iostream>
#include <numeric>

/*
	将数组分为两组
	每组的异或和相同，并且其中一组尽可能大

	因为每组的异或和相同，两个数组的异或和就是0，所以数组的总异或和为0

	所以取出任一一个数，剩下的元素的异或和与该数相等
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

