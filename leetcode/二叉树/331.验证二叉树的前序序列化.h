#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	�涨��������ǰ������ַ���Ϊ��ÿ��Ԫ�ؼ���','�������սڵ�Ϊ'#'
	�ж�һ���ַ����Ƿ�����Ч�Ķ�����ǰ�����

	������ǰ����������Ե�һ��Ԫ���Ǹ��ڵ㣬�ڶ���Ԫ�����������ĸ��ڵ�
	������������λ�ò���֪��
	���Եݹ��ȥ�����������������䷵�����ĳ��ȣ��Ӷ�ȷ�����������ڵ��λ��
	�������'#'��ֱ�ӷ���1������ջ��߷�'#'���ǳ���С��5��Ҷ�ӽڵ������ǣ� "X��#��#"������Ϊ5�������ַ�����Ч
*/

bool isValidSerialization(string preorder) {
	bool ans = true;
	auto recursion = [&ans](this auto&& recursion, string_view str)->int
		{
			if (!ans)return 0; // �Ѿ���Ч���������
			auto i = str.find(',');
			if (string::npos == i)
			{
				i = str.size();
			}

			if ("#" == str.substr(0, i))
			{
				return 1;
			}

			if (str.size() < 5)
			{
				ans = false;
				return 0;
			}

			// �õ��������ĳ��ȣ�Ȼ��ȷ������������㣬�ݹ�������
			auto left_size = recursion(str.substr(i + 1));
			auto right_size = recursion(str.substr(1 + i + left_size + 1));
			// ���� i + 1 + left_size + 1 + right_size 
			return i + 1 + left_size + 1 + right_size;
		};

	return recursion(preorder) == preorder.size() && ans;
}

/*
	��ѧ�ⷨ��������ֵݹ飩
	���һ���ڵ����ӽڵ㣬����Ϊ�������ָ���ӽڵ�ı�
	�ӽڵ����������Ը��ڵ�ıߣ���������ͬ
	���ڿսڵ㣬��ֻ���ı߲������ߣ����ڸ��ڵ㣬ֻ�����߲����ı�
	���ĳһʱ�����ĵı߸��࣬�����
	�㷨���������edge==0��true
*/

bool isValidSerialization(string preorder) {
	int edge = 1;
	stringstream ss{ preorder };
	string node;
	while (getline(ss, node, ','))
	{
		--edge;
		if (edge < 0)return false;
		if (node != "#")
		{
			edge += 2;
		}
	}

	return 0 == edge;
}