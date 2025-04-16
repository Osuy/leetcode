#pragma once

#include "base_header.h"
namespace std {
	template<>
	struct hash<vector<int>> {
		size_t operator()(const vector<int>& vec) const {
			size_t seed = vec.size();
			for (int i : vec) {
				seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
			return seed;
		}
	};
}

int shoppingOffers(const vector<int>& price, const vector<vector<int>>& special, const vector<int>& needs) {
	unordered_set<size_t> payed;

	int pay = 0;
	vector<int> rest = needs;
	int min_pay = INT_MAX;

	// auto rescursion = [&](this auto&& rescursion)->void
	std::function<void()> rescursion = [&]()->void
		{
			auto key = pay + std::hash<vector<int>>{}(rest);
			if (payed.contains(key))return;
			payed.insert(key);
			if (all_of(rest.begin(), rest.end(), [](int num) {return num == 0; }))
			{
				min_pay = min(min_pay, pay);
				return;
			}

			for (int i = 0;i < rest.size();++i)
			{
				if (rest[i] < 1)continue;

				rest[i]--;
				pay += price[i];
				rescursion();
				pay -= price[i];
				rest[i]++;
			}

			for (const auto& el : special)
			{
				bool excceed = false;
				for (int i = 0;i < rest.size();++i)
				{
					if (el[i] > rest[i])
					{
						excceed = true;
						break;
					}
				}

				if (excceed)continue;

				for (int i = 0;i < rest.size();++i)
				{
					rest[i] -= el[i];
				}
				pay += el.back();

				rescursion();

				pay -= el.back();
				for (int i = 0;i < rest.size();++i)
				{
					rest[i] += el[i];
				}
			}
		};

	rescursion();

	return min_pay;
}

int test638()
{
	return shoppingOffers({ 1,1,1 }, { {1,1,0,0,}, {2,2,1,0} }, { 1,1,1 });
}