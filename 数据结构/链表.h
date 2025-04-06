#pragma once
#include <vector>

/*
	������ص��㷨�޷Ǿ��ǲ���pre��next�Լ�next->next��

	��ͷ�ڵ��ʹ�������࣬C++��׼��listҲ�Ǵ�ͷ�ڵ��
	list_node_t dummy{};
	auto node = &dummy; 
	Ȼ����nodeȥ������Ҫ���������
	�������dummy���� auto node = head; ����Ҫ�����node��ʼ����һЩ����
	Ȼ����ѭ������ͬ�Ĵ�������dummy����ֱ�ӿ�ʼѭ����


�����ⵥ
	�������Ŀ����һ���ļ����Ի�ͷ�Է籩��һ��Ҫ���ͼ������֪�����������Կ���ָ�롢�̶����ڵ�
	Ҫ�γ�ָ���������Ķ�̬��ͼ��֪��ָ��Ҫȥ����߶೤��

	86.�ָ��б�����ڵ㻥��������

	�󣺵�����ĵ�����N���ڵ㡣���̶����ڣ�
	������ֻ��������������Բ�֪�����ȵ�����µ�����N���޷��Ƴ��������ڼ���
	��ȻΨһֱ������N����ô����һ��ָ��p1��������N���ڵ㣬Ȼ��ڶ���ָ��p2�ٿ�ʼ����
	ֱ��p1Ϊ�ա�����p1��2���ΪN��p1ָ��������ĩβ����p2ָ��ľ��ǵ�N���ڵ�


	876.�������м�Ľڵ㡣������ָ�룩
	�������󳤶��ٱ������м�ķ������⡣�����һ�⣬p2��p1���n������p1��ĩβʱp2�ǵ�����n
	��������Կ�����p1��ĩβʱp2���м䣬��ôֻ��Ҫp1��ǰ���ٶ�ʱp2����������
	���������ͬ�Ĵ���Ҳ���Խ������ɻ����⡣�������ɻ���p1�ܻ�Ӻ���׷��p2

	141.�������Ƿ���ڻ�������ָ�룩
	���������ɻ�������ʱ��ص������㡣ֻ��Ҫ��¼ÿ�����Ƿ񱻱���������
	���Ǵ��ڶ���Ŀռ临�Ӷȡ��������ÿ���ָ�룬��ָ��һ����׷����ָ��

	142.������㣨����Ҫ���뵽��㵽�� == ���㵽����
	�������ָ������ʱǰ����M�Σ���ָ�����2M�Ρ���ָ�������M��Ҳ�����˼�Ȧ�������ܲ�ֹһȦ��
	����M�ǻ��ܳ���������
	�軷���ΪN�������ָ���ʱ�ڻ���M-N���������N����ָ����ܵ��ﻷ��㡣�պû����Ҳ�ǵ�N��
	���ǰ���ָ�������㣬��ָ����ǰ�ߣ�һ���٣������������ڻ����

	160.����������ڽ��㣬�����ʱ�临�Ӷ�O(m+n)�Ϳռ临�Ӷ�O(1)�������ҵ����㣨��������ͬ�������ϲ����ǲ��ǿ���ָ�붼��һ����������Ҫ����ָ��������·�ǵȳ��Ĳ��У�
	ͷ�Է籩�����ֽⷨ��
		1.������һ�������ͷβ����γɻ����ͱ�����󻷵���㡣������
		2.��A�ͱ�Bͬʱ�������ǿ���ָ�룬�����ܱ�ָ֤�����������Ϊ���ǳ���δ֪
			����������������һ�¾Ϳ���ʹָ��������������
			��A�� A���е����� + ��������
			��B�� B���е����� + ��������
			�ֱ�����Ǽ��϶Է��Ķ������䣬���ܿ��Ƴ���һ�¡�����ֱ�Ӽ��������Է��ı�
			��A�� A���е����� + �������� + B���е����� + ��������
			��B�� B���е����� + �������� + A���е����� + ��������
			����ָ��ֱ����A+B��B+A������ʱ���ǽ���
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

		// p1��ǰ��n
		int m = n;
		while (p1 && m--) p1 = p1->next;

		if (!p1)return;

		// p2��p1��ʼͬ��ǰ��
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