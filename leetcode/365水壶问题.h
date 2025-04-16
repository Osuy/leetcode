#pragma once
#include "base_header.h"

/*
	�Ѷȣ��е�
	��Ŀ����������ˮ�������޵�ˮ�����ܷ�ճ�ָ��������ˮ
		���ԵĲ�����1.װ��һ��ˮ����2.����һ��ˮ����3.��һ��ˮ����ˮ������һ��ˮ����ֱ������һ�������

	���������ܷ�ճ����������޿���dfs������ʴճ������ٲ���������ô��bfs��
        ���⻹�д���ѧ�ⷨ
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
    ����ѧ�ⷨ
    target��x��y�����Լ���ı�������
*/

bool canMeasureWater3(int x, int y, int target) {
	if (x + y < target)return false;
	return target % std::gcd(x, y) == 0;

}