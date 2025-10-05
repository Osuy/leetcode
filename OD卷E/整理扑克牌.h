#pragma once
#include <vector>
#include <xutility>
#include <algorithm>
/*
	炸弹：4
	葫芦：3+2
	三张：3
	对子：2
	单张：1
*/

template<unsigned N>
void pusher(std::vector<int>& dest, std::vector<int>& vec)
{
	for (auto el : vec)
	{
		for (int i = 0; i < N; ++i)
		{
			dest.push_back(el);
		}
	}
}

std::vector<int> trimPoke(const std::vector<int>& pokes)
{
	int counts[13];
	memset(&counts, 0, sizeof(counts));

	for (auto el : pokes)
	{
		counts[el]++;
	}
	std::vector<int>res;
	std::vector<int> v4, v3, v2, v1;
	for (int i = 0; i < 13; ++i)
	{
		switch (counts[i])
		{
		case 0:break;
		case 1:v1.push_back(i); break;
		case 2:v1.push_back(i); break;
		case 3:v1.push_back(i); break;
		default: v4.push_back(i);
		}
	}

	std::sort(v4.begin(), v4.end(), std::greater<int>{});
	std::sort(v3.begin(), v3.end(), std::greater<int>{});
	std::sort(v2.begin(), v2.end(), std::greater<int>{});
	pusher<4>(res, v4);

	while (!v3.empty())
	{
		auto val = v3.back();
		v3.pop_back();
		res.push_back(val);
		res.push_back(val);
		res.push_back(val);

		if (!v3.empty())
		{
			val = v3.back();
			v3.pop_back();
			res.push_back(val);
			res.push_back(val);
			v1.push_back(val);
		}
		else if (!v2.empty())
		{
			val = v2.back();
			v2.pop_back();
			res.push_back(val);
			res.push_back(val);
		}
	}

	pusher<2>(res, v2);
	
	// v1可能加入了v3的元素，所以最后再排序
	std::sort(v1.begin(), v1.end(), std::greater<int>{});
	pusher<1>(res, v1);
}