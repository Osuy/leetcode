#include "Á´±í.h"

list_t::node_t* list_t::mergeKLists(std::vector<node_t*>& lists)
{
	std::deque<node_t*> heap;
	for (auto list : lists)
	{
		while (list)
		{
			heap.push_back(list);
			list = list->next;
		}
	}

	int sum = heap.size();
	for (int i = sum / 2 - 1; i >= 0; --i)
	{
		int n = i;
		while (n * 2 + 2 < sum || n * 2 + 1 < sum)
		{
			int min = n;
			if (n * 2 + 1 < sum && heap[n * 2 + 1]->val < heap[min]->val)min = n * 2 + 1;
			if (n * 2 + 2 < sum && heap[n * 2 + 2]->val < heap[min]->val)min = n * 2 + 2;
			if (min == n)break;

			std::swap(heap[min], heap[n]);
			n = min;
		}
	}

	node_t dummy{};
	auto node = &dummy;
	while (!heap.empty())
	{
		node->next = heap[0];
		node = node->next;
		heap[0] = heap.back();
		heap.pop_back();
		int n = 0;
		int size = heap.size();
		while (n * 2 + 2 < size || n * 2 + 1 < size)
		{
			int min = n;
			if (n * 2 + 1 < size && heap[n * 2 + 1]->val < heap[min]->val)min = n * 2 + 1;
			if (n * 2 + 2 < size && heap[n * 2 + 2]->val < heap[min]->val)min = n * 2 + 2;
			if (min == n)break;

			std::swap(heap[min], heap[n]);
			n = min;
		}
	}

	return dummy.next;
}

