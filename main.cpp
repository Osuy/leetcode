#include <iostream>
//#include"56.�ϲ�����.h"
//#include "����.h"
//#include "leetcode/2132.��Ʊ��������.h"
//#include  "���ݽṹ/ͼ.h"
//#include "���ݽṹ/����.h"
#include "leetcode/221���������.h"
using std::cout;
using std::endl;

class A
{
protected:
	int a = 0;
};

void func(A& obj)
{
	obj.a;// ���� ���ʱ�����Ա

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