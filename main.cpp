#include <iostream>
//#include"56.�ϲ�����.h"
//#include "����.h"
//#include "leetcode/2132.��Ʊ��������.h"
//#include  "���ݽṹ/ͼ.h"
//#include "���ݽṹ/����.h"
#include "leetcode/221���������.h"
#include "leetcode/638�����.h"
#include  "���ݷ�.h"
#include "leetcode/ջ/388.�ļ������·��.h"
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