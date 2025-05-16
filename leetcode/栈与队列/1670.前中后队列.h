#pragma once
#include "../base_header.h"

namespace q1670
{
class FrontMiddleBackQueue {
public:
	list<int>ctn;
	list<int>::iterator mid;
	FrontMiddleBackQueue()
		:ctn{}
		, mid{ ctn.end() }
	{
	}

	void pushFront(int val)
	{
		ctn.push_front(val);
		if (1 == ctn.size())
		{
			mid = ctn.begin();
		}
		else if (ctn.size() % 2)
		{
			--mid;
		}
	}

	void pushMiddle(int val)
	{
		ctn.insert(mid, val);
		if (ctn.size() % 2)
		{
			--mid;
		}
	}

	void pushBack(int val)
	{
		ctn.push_back(val);
		if (1 == ctn.size())
		{
			mid = ctn.begin();
		}
		else if (0 == ctn.size() % 2)
		{
			++mid;
		}
	}

	int popFront() {
		if (ctn.empty())return -1;
		if (1 == ctn.size())
		{
			mid = ctn.end();
		}
		else if (ctn.size() % 2)
		{
			++mid;
		}
		int ans = ctn.front();
		ctn.pop_front();
		return ans;
	}

	int popMiddle() {
		if (ctn.empty())return -1;
		if (0 == ctn.size() % 2)
			--mid;
		int ans = *mid;
		mid = ctn.erase(mid);
		return ans;
	}

	int popBack() {
		if (ctn.empty())return -1;
		if (1 == ctn.size())
		{
			mid = ctn.end();
		}
		else if (0 == ctn.size() % 2)
		{
			--mid;
		}
		int ans = ctn.back();
		ctn.pop_back();

		return ans;
	}
};

void test()
{
	FrontMiddleBackQueue q;
	q.pushFront(1);
	q.pushFront(2);
	q.pushFront(3);
	q.pushFront(4);
	q.popBack();
	q.popBack();
	q.popBack();
	q.popBack();
	q.popMiddle();
	q.pushMiddle(45652);
	q.popBack();
	q.pushMiddle(529290);
	q.pushMiddle(137216);
	q.pushMiddle(541778);
	q.pushMiddle(579220);
	q.popMiddle();
	q.popBack();
	q.popMiddle();
	q.popFront();
	q.pushMiddle(84471);
	q.popFront();
	q.popMiddle();
	q.popMiddle();
	q.pushMiddle(890665);
	q.popMiddle();
	q.popMiddle();
	q.popMiddle();
	q.pushMiddle(432059);
	q.popMiddle();
	q.pushMiddle(672417);
	q.popMiddle();
	q.popMiddle();
	q.pushMiddle(978882);
	q.popMiddle();
	q.popMiddle();
	q.pushMiddle(386335);
	q.pushMiddle(986878);
	q.pushMiddle(92639);
	q.popMiddle();
	q.popMiddle();
	q.popMiddle();
	q.pushMiddle(391909);
	q.pushMiddle(592975);
	q.pushMiddle(992188);
	q.popFront();
	q.popMiddle();
	q.pushMiddle(645886);
	q.popBack();
	q.popBack();
	q.popMiddle();
	q.popMiddle();
}
}