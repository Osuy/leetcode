//#include"56.合并区间.h"
#include "排序.h"
#include "leetcode/2132.邮票铺满网格.h"
#include  "数据结构/图.h"
#include <iostream>
#include "数据结构/链表.h"
using std::cout;
using std::endl;

int main()
{
	Solution obj{};
	vector<vector<int>>matrix
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};

	vector<int> arr{ 110,100,0, 9, 43, 67,88,4,12 };
	heap_sort(arr);
	
	obj.possibleToStamp(matrix,  2, 2);
	auto p1 = std::make_shared<list_t::node_t>(-2);
	auto p2 = std::make_shared<list_t::node_t>(-1);
	auto p3 = std::make_shared<list_t::node_t>(-1);
	auto p4 = std::make_shared<list_t::node_t>(-1);
	p1->next = p2.get();
	p2->next = p3.get();
	p3->next = p4.get();
	vector<list_t::node_t*> lists{ p1.get(), nullptr };
	list_t::mergeKLists(lists);
	return 0;
}