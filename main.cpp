#include <iostream>
//#include"56.合并区间.h"
//#include "排序.h"
//#include "leetcode/2132.邮票铺满网格.h"
//#include  "数据结构/图.h"
//#include "数据结构/链表.h"
#include "leetcode/221最大正方形.h"
#include "leetcode/638大礼包.h"
#include  "回溯法.h"
#include "leetcode/栈/388.文件最长绝对路径.h"
#include <set>
using std::cout;
using std::endl;

class A
{
public:
	A() {}
	A(const A&)
	{
		cout << "A::copy contructor" << endl;
	}

	A& operator=(const A&)
	{
		cout << "A::assignment operator" << endl;
		return *this;
	}
};

class B
{
public:
	A a;
};

int main()
{
	B b;
	B c = b;
	B d;
	d = c;

	std::set<int> s;
	std::priority_queue<int>q;
	//test();
	cout << test221() << endl;
	cout << test638() << endl;
	q388::test();
	return 0;
}