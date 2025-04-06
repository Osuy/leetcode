#pragma once
#include <vector>

/*
	链表相关的算法无非就是操作pre和next以及next->next等

	带头节点会使代码更简洁，C++标准库list也是带头节点的
	list_node_t dummy{};
	auto node = &dummy; 
	然后用node去遍历需要处理的链表
	如果不用dummy，用 auto node = head; 还需要额外对node初始化做一些处理
	然后再循环做相同的处理。用了dummy就能直接开始循环了


链表题单
	链表的题目都有一定的技巧性或头脑风暴。一定要结合图例和已知的条件，尝试快慢指针、固定窗口等
	要形成指针遍历链表的动态视图，知道指针要去哪里，走多长度

	86.分隔列表（链表节点互换操作）

	求：单链表的倒数第N个节点。（固定窗口）
	单链表只能正向遍历，所以不知道长度的情况下倒数第N个无法推出是正数第几个
	既然唯一直到的是N，那么先让一个指针p1遍历到第N个节点，然后第二个指针p2再开始遍历
	直到p1为空。由于p1和2间隔为N，p1指向了链表末尾所以p2指向的就是第N个节点


	876.单链表中间的节点。（快慢指针）
	除了先求长度再遍历到中间的方法以外。结合上一题，p2和p1间隔n，所以p1到末尾时p2是倒数第n
	而此题可以看成是p1到末尾时p2到中间，那么只需要p1的前进速度时p2的两倍即可
	而这道题相同的代码也可以解决链表成环问题。如果链表成环，p1总会从后面追上p2

	141.单链表是否存在环（快慢指针）
	如果单链表成环，遍历时会回到环交点。只需要记录每个点是否被遍历过即可
	但是存在额外的空间复杂度。可以利用快慢指针，快指针一定会追上慢指针

	142.环的起点（必须要联想到起点到环 == 交点到环）
	假设快慢指针相遇时前进了M次，快指针就是2M次。快指针多走了M格，也多走了几圈环（可能不止一圈）
	于是M是环周长的整数倍
	设环起点为N，则快慢指针此时在环内M-N格。如果再走N格，慢指针就能到达环起点。刚好环起点也是第N格
	于是把慢指针设回起点，快指针往前走（一倍速）。二者相遇在环起点

	160.两个链表存在交点，如何在时间复杂度O(m+n)和空间复杂度O(1)条件下找到交点（在两个不同的链表上不论是不是快慢指针都不一定相遇，需要控制指针所都的路是等长的才行）
	头脑风暴，两种解法：
		1.将其中一个链表的头尾相接形成环，就变成了求环的起点。见上文
		2.表A和表B同时遍历还是快慢指针，都不能保证指针会遇到。因为它们长度未知
			假如能让两个表长度一致就可以使指针相遇。分析：
			表A： A独有的区间 + 共有区间
			表B： B独有的区间 + 共有区间
			分别给它们加上对方的独有区间，就能控制长度一致。不妨直接加上整个对方的表
			表A： A独有的区间 + 共有区间 + B独有的区间 + 共有区间
			表B： B独有的区间 + 共有区间 + A独有的区间 + 共有区间
			两个指针分别遍历A+B和B+A，相遇时就是交点
*/
class list_t
{
public:
	struct list_node_t
	{
		int val = 0;
		list_node_t* next = nullptr;
	};
private:
	list_node_t _dummy{};
public:
	list_t() {}
	list_t(const std::vector<int>& arr)
	{
		auto node = &_dummy;
		for (int i = 0; i < arr.size(); ++i)
		{
			node->next = new list_node_t{ arr[i] };
			node = node->next;
		}
	}
	~list_t() 
	{
		auto node = _dummy.next;
		while (node)
		{
			auto t = node;
			node = node->next;
			delete t;
		}
	}

	int get(int index) {
		auto node = _dummy.next;
		while (index-- && node) node = node->next;
		if (node)
			return node->val;

		return -1;
	}

	void addAtHead(int val) {
		auto node = new list_node_t{ val };
		node->next = _dummy.next;
		_dummy.next = node;
	}

	void addAtTail(int val) {
		auto node = &_dummy;
		while (node->next) node = node->next;
		node->next = new list_node_t{ val };
	}

	void addAtIndex(int index, int val) {
		auto node = &_dummy;
		while (index-- && node->next) node = node->next;
		if (index < 0)
		{
			auto t = node->next;
			node->next = new list_node_t{ val };
			node->next->next = t;
		}
	}

	void deleteAtIndex(int index) {
		auto node = &_dummy;
		while (index-- && node->next) node = node->next;
		if (node->next)
		{
			auto t = node->next;
			node->next = node->next->next;
			delete t;
		}
	}

	list_node_t* get_last_n(int n)
	{
		auto p1 = &_dummy;

		// p1先前进n
		int m = n;
		while (p1 && m--) p1 = p1->next;

		if (!p1)return;

		// p2和p1开始同步前进
		auto p2 = &_dummy;
		while (p1)
		{
			p2 = p2->next;
			p1 = p1->next;
		}

		return p2;
	}

	list_node_t* get_last_mid()
	{
		auto p1 = &_dummy;
		auto p2 = &_dummy;
		while (p1)
		{
			p2 = p2->next;
			p1 = p1->next;
			if (p1)
				p1 = p1->next;
		}

		return p2;
	}

	bool has_loop()const
	{
		auto p1 = &_dummy;
		auto p2 = &_dummy;
		while (p1)
		{
			p2 = p2->next;
			p1 = p1->next;
			if (p1)
			{
				p1 = p1->next;
				if (p1 == p2) return true;
			}

		}

		return false;
	}

	list_node_t* get_circle_start()
	{
		auto p1 = &_dummy;
		auto p2 = &_dummy;

		while (p1 && p1->next)
		{
			p1 = p1->next->next;
			p2 = p2->next;
		}

		if (!p1 || !p1->next)return nullptr;

		p2 = &_dummy;
		while (p1 && p1 != p2)
		{
			p1 = p1->next;
			p2 = p2->next;
		}

		return p1;
	}

	list_node_t* get_cross(list_node_t* list1, list_node_t*list2)const
	{
		auto p1 = list1;
		auto p2 = list2;

		while (p1 && p2 && p1 != p2)
		{
			p1 = p1->next;
			p2 = p2->next;
		}

		if (!p1)p1 = list2;
		else p2 = list1;

		while (p1 && p2 && p1 != p2)
		{
			p1 = p1->next;
			p2 = p2->next;
		}

		return p1;
	}
};