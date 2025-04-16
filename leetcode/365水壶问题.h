#pragma once
#include "base_header.h"

/*
	难度：中等
	题目：给出两个水壶和无限的水，求能否凑出指定容量的水
		可以的操作：1.装满一个水壶；2.倒空一个水壶；3.将一个水壶的水倒到另一个水壶，直至任意一个满或空

	分析：求能否凑出，所以有限考虑dfs（如果问凑出的最少操作数，那么用bfs）
        另外还有纯数学解法
*/
union qel_t
{
	unsigned long long w = 0;
	struct
	{
		int x;
		int y;
	};
};

// dfs
bool canMeasureWater(int x, int y, int target)
{
	std::function<void(qel_t&)> ops[6] =
	{
		[x](qel_t& qel) {qel.x = x;},
		[y](qel_t& qel) {qel.y = y;},
		[](qel_t& qel) {qel.x = 0;},
		[](qel_t& qel) {qel.y = 0;},
		[x](qel_t& qel)
		{
			int tmp = x - qel.x;
			if (tmp > qel.y)
			{
				qel.x += qel.y;
				qel.y = 0;
			}
			else
			{
				qel.x = x;
				qel.y -= tmp;
			}
		},
		[y](qel_t& qel)
		{
			int tmp = y - qel.y;
			if (tmp > qel.x)
			{
				qel.y += qel.x;
				qel.x = 0;
			}
			else
			{
				qel.x -= tmp;
				qel.y = y;
			}
		}
	};

	std::unordered_set<unsigned long long> set;
	set.insert(0);

    std::function<bool(const qel_t&)> backtrace = [&](const qel_t&qel)
        {
            if (qel.x == target || qel.y == target || (qel.y + qel.x) == target)return true;


            for (int i = 0;i < 6;++i)
            {
				auto qel2 = qel;
				ops[i](qel2);
                if (set.contains(qel2.w)) continue;
				
				set.insert(qel2.w);
				if (backtrace(qel2)) return true;
				
			}
			return false;
        };

    return backtrace({0});
}

// bfs
bool canMeasureWater2(int x, int y, int target) {
    /*

    */
    std::function<void(qel_t&)> ops[6] =
    {
        [x](qel_t& qel) {qel.x = x;},
        [y](qel_t& qel) {qel.y = y;},
        [](qel_t& qel) {qel.x = 0;},
        [](qel_t& qel) {qel.y = 0;},
        [x](qel_t& qel)
        {
            int tmp = x - qel.x;
            if (tmp > qel.y)
            {
                qel.x += qel.y;
                qel.y = 0;
            }
            else
            {
                qel.x = x;
                qel.y -= tmp;
            }
        },
        [y](qel_t& qel)
        {
            int tmp = y - qel.y;
            if (tmp > qel.x)
            {
                qel.y += qel.x;
                qel.x = 0;
            }
            else
            {
                qel.x -= tmp;
                qel.y = y;
            }
        }
    };

    std::unordered_set<unsigned long long> set;
    set.insert(0);
    std::queue<qel_t> q;
    q.push({ 0 });
    while (!q.empty())
    {
        auto qel = q.front();
        q.pop();

        if (qel.x == target
            || qel.y == target
            || (qel.x + qel.y) == target) return true;

        for (int i = 0;i < 6;++i)
        {
            auto qel2 = qel;
            ops[i](qel2);
            if (!set.contains(qel2.w))
            {
                set.insert(qel2.w);
                q.push(qel2);
            }
        }
    }

    return false;
}
/*
    纯数学解法
    target是x和y的最大公约数的倍数即可
*/

bool canMeasureWater3(int x, int y, int target) {
	if (x + y < target)return false;
	return target % std::gcd(x, y) == 0;

}