#include <iostream>
//#include"56.�ϲ�����.h"
//#include "����.h"
//#include "leetcode/2132.��Ʊ��������.h"
//#include  "���ݽṹ/ͼ.h"
//#include "���ݽṹ/����.h"
#include "leetcode/221���������.h"
#include "leetcode/638�����.h"
#include  "���ݷ�.h"
#include "leetcode/ջ�����/388.�ļ������·��.h"
#include "leetcode/ջ�����/1670.ǰ�к����.h"
#include "leetcode/������/297.�����������л��뷴���л�.h"
#include "leetcode/������/98.��֤����������.h"
#include "leetcode/��̬�滮/53.����������.h"
#include "OD��E/��������淽��.h"
#include "OD��E/ת����.h"
#include "OD��E/������ִ�.h"
#include "�������Ʊ�����.h"
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