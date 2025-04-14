#include <iostream>
//#include"56.合并区间.h"
//#include "排序.h"
//#include "leetcode/2132.邮票铺满网格.h"
//#include  "数据结构/图.h"
//#include "数据结构/链表.h"
#include "leetcode/221最大正方形.h"
using std::cout;
using std::endl;

class A
{
protected:
	int a = 0;
};

void func(A& obj)
{
	obj.a;// 不能 访问保护成员

	auto b = struct : public A { using A::a; }{obj};

	[](B&& obj)
	{
		obj.a;
	} ({ obj });
}


int main()
{
	A obj;
	func(obj);
	cout << test221() << endl;
	return 0;
}