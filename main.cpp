#include <iostream>
//#include"56.合并区间.h"
//#include "排序.h"
//#include "leetcode/2132.邮票铺满网格.h"
//#include  "数据结构/图.h"
//#include "数据结构/链表.h"
#include "leetcode/221最大正方形.h"
#include "leetcode/638大礼包.h"
#include  "回溯法.h"
#include <set>
using std::cout;
using std::endl;

int main()
{
	std::set<int>  q;
	std::priority_queue<int, std::greater<>>q;
	test();
	cout << test221() << endl;
	cout << test638() << endl;
	return 0;
}