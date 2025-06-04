#pragma once

/*
	难度：中等
	考查数学知识

	x的n次方，可以对n进行2的次幂的因式分解
	n的二进制上的每一位bit，都代表有无该位的2次幂
	例如 22 = 10110 = 1(2^4) + 0(2^3) +  1(2^2) + 1(2^1) + 0(2^0)
	由于n是指数，底数相乘等于指数相加，于是可以逆运算指数相加 = 底数相乘

	从低到高遍历n的bit，对于第i位，如果位1， 则乘上 x^2^i，这个乘式也可以在每次循环体内 x=*x 
*/

double myPow(double x, int n) {
	long long m = n;
	if (n < 0)
	{
		x = 1 / x;
		m = -m;
	}

	double ans = 1.0;
	while (m)
	{
		if (m & 1)
		{
			ans *= x;
		}
		x *= x; // 平方一下，等效与 x^(2^i)
		m >>= 1;
	}

	return ans;
}