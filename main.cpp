#include <iostream>
//#include"56.合并区间.h"
//#include "排序.h"
//#include "leetcode/2132.邮票铺满网格.h"
//#include  "数据结构/图.h"
//#include "数据结构/链表.h"
#include "leetcode/221最大正方形.h"
#include "leetcode/638大礼包.h"
#include  "回溯法.h"
#include "leetcode/栈与队列/388.文件最长绝对路径.h"
#include "leetcode/栈与队列/1670.前中后队列.h"
#include "leetcode/二叉树/297.二叉树的序列化与反序列化.h"
#include "leetcode/二叉树/98.验证二叉搜索树.h"
#include "leetcode/动态规划/53.最大子数组和.h"
#include "OD卷E/最长连续交替方波.h"
#include "OD卷E/转骰子.h"
#include "OD卷E/最长条件字串.h"
#include "网易烟云笔试题.h"
#include <set>
#include <numeric>
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
	//B b;
	//B c = b;
	//B d;
	//d = c;

	//std::set<int> s;
	//std::priority_queue<int>q;
	////test();
	//cout << test221() << endl;
	//cout << test638() << endl;
	//q388::test();
	//q1670::test();
	//q297::test();

	//q1::test();
	//q3::test();
	//q4::test();

	// yanyun::test();
	auto ptr = new char[33554432];
	std::iota(ptr, ptr + 33554432, 0);

	auto ptr2 = new char[33554432];
	memcpy(ptr2, ptr, 33554432);

	delete ptr;
	delete ptr2;

	return 0;
}