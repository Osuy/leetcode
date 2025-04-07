#pragma once
#include <vector>
using std::vector;

/*
	ѡ������
	�����������˼·���ҵ�δ������������С��Ԫ�أ�������������ĩβ����һ��Ԫ�ػ�������������������δ����������С��
	����δ���������ڵ�Ԫ�ط����Ļ����������ȶ��Բ�

	�����Ƕ����Ѿ�������������飬������Ҫȷ��δ�����������СԪ�أ�����Ҫ����������ʱ�临�Ӷ�����O(n^2)
*/
void select_sort(vector<int>& arr)
{
	int size = arr.size();
	for (int i = 0; i < size - 1; ++i)
	{
		// �ҵ�[i, size)�ڵ���СԪ�أ���i����
		int i_min = i;
		for (int j = i; j < size; ++j)
		{
			if (arr[j] < arr[i_min])
			{
				i_min = j;
			}
		}
		std::swap(arr[i], arr[i_min]);
	}
}

/*
	ð������
	�Ż����ȶ��ԡ�ÿ�δ�δ��������Ѱ����СԪ��ʱ�����Ǻ�����������ĩβ����һ��Ԫ�ػ���
	���ǽ�ǰ�������δ����Ԫ��������ƣ�ʹ���Ǳ����ȶ�
	������ƣ��ڲ������ǣ���ǰ������ÿһ��Ԫ�ػ���
	�����ѭ����������������

	��һ�ֽ����ǣ��Ӻ���ǰ����ÿ��Ԫ�����С�Ļ���ǰ�棬���һ����ѭ��ʱ����С��Ԫ�ؾͻḡ��

	����ֻ�������Ԫ�ػụ�������ڻ���ڵ�Ԫ�ػ�������ƣ����Ա���ѡ�������и��õ��ȶ���
	��Ȼ��Ҫ֪��δ�����������СԪ�أ�ʱ�临�Ӷ�����O(n^2)
*/
void bubble_sort(vector<int>& arr)
{
	int size = arr.size();
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = size - 1;j > i;--j)
		{
			if (arr[j] < arr[j - 1])
			{
				std::swap(arr[j], arr[j - 1]);
			}
		}
	}
}

/*
	��������
	��һ���Ż������ǽ�δ���������ڵĴ�����СԪ�صĲ����������
	���ǽ������������ڴ�������Ԫ�صĲ���������ơ���������Ԫ�ز��뵽������������
	������ȫû�в���δ�������䣬��Ȼ�����ȶ���
	���⣬�����Ѿ�������������飬���������ڲ��Ҳ���λ��ʱ�������ɡ�������ʱ��ʱ�临�Ӷ�ΪO(n)���ʱҲ�ź�ѡ��ð��һ��
	������ȶ��Ժ����ܡ�std::sort��Ԫ��С��47ʱ�ͻ�ʹ�ò�������

	�ʣ�Ϊʲô����������������Ѱ����Ԫ�ص�λ�ò��ö��ֲ��ң�
	�𣺼���ʹ���˶��ֲ��ң�����Ҫ���Ʋ��������Ӷ�����O(n^2)�����Բ���򻯴���
*/
void insert_sort(vector<int>& arr)
{
	int size = arr.size();
	for (int i = 1; i < size; ++i)
	{
		// ���� arr[i]
		// �������������������ѣ�ֱ��arr[j] <= key
		int key = arr[i];
		int j = i;
		while (0 < j && key < arr[j - 1]) //�˳�ѭ��ʱ��j>=0
		{
			arr[j] = arr[j - 1];
			--j;
		}

		arr[j] = key;
	}
}

/*
	ϣ������
	�Բ���������Ż���ʵ����O(n^2)��O(nlogn)��ͻ��
	ǰ���ᵽ����������������������������������������в�����Ԫ�ء�ʱ�临�Ӷ���õ������O(n)
	�Ǽ�����ǰ�����鴦��ʹ���������򣬾����Ż���������
	ϣ��������뷨�ǣ��������Ϊ����飬ÿ����������Ԫ�أ�Ȼ��ÿ���鶼����ΪС����ǰ������ں�
	��Ҫ��ô�����أ�������һ���𣿲��ǡ��ǽ����������Ϊǰ�벿�ֺͺ�벿�֣�Ȼ��ÿ�����ֵ�Ԫ��һһ���
	����һ�Ρ��������󣬾����������ϴ���ٺ���С����ǰ��
	�����֡����������ǲ�������

	�����һ�����������󣬷�������Ϊ�������ظ�����
	ֱ����������ΪN��ִ�����һ�Ρ���������Ҳ���ǲ������򡣵õ���

	�������ڷ����ˣ���ͬԪ�طֵ���ͬ��ʱ���ܸı�λ�ã�����ʧȥ���ȶ��ԡ�
*/

void shell_sort(vector<int>& arr)
{
	int size = arr.size();
	int gap = size / 2;

	while (0 < gap)// gap��С��0�˳�ѭ��
	{
		for (int i = gap; i < size; ++i)//��ָ��1��Ϊָ���0������ĵ�1������gap�����Ǳ�������Ȼ����������
		{
			int key = arr[i];
			int j = i;
			while (gap <= j && key < arr[j - gap]) // ���뵽�Լ��ķ����ڣ��� ǰn*gap��Ԫ����
			{
				arr[j] = arr[j - gap];
				j -= gap;
			}

			arr[j] = key;
		}

		gap /= 2;// gap��С
	}
}

/*
	��������
	������ǰ�����˼ά
	��ȡһ����׼��Ϊ����ֱ��ʹ�õ�0��Ԫ�أ�һ��Ҫ���ȡ��
	Ȼ������С�ڻ�׼�ķŵ�ǰ�棬�����ڵ��ڻ�׼�ķŵ����棬Ȼ���׼�ŵ��м�
	֮���ٶ������������ұ��������ظ�����
	ÿ�β�������N�Σ�����Ϊ�����ظ�������һ���ظ�logN�β���������ʱ�临�Ӷ���O(NlogN)

	��Ϊ��ԭ�����򣬿ռ临�Ӷ�O(1)
	���Ƕ��ڣ����׼����ͬԪ�أ�ԭ���ڻ�׼ǰ�󶼿��ܣ����Ƕ����ŵ���׼���棬˳�����ı�
	�����ǲ��ȶ�������
*/
void qsort(vector<int>& nums, int l, int r)
{
	// ���䳤�Ƚ�Ϊ1��߽���Ч������
	if (r - l < 2)return;

	// ��λ��front��back
	int f = l, b = r - 1;
	int key = nums[(f + b)/2];
	nums[(f + b) / 2] = nums[f];
	while (f < b)
	{
		while (f < b&& key <= nums[b])--b;
		nums[f] = nums[b];
		while (f < b && nums[f] <= key)++f;
		nums[b] = nums[f];
	}

	nums[f] = key;

	qsort(nums, l, f);
	qsort(nums, f + 1, r);
}

void qsort(vector<int>& nums)
{
	qsort(nums, 0, nums.size());
}

/*
	�鲢����
	�����������������Ƚ���������������Ȼ��ϲ�

	������
		�ȴӳ���1�����鿪ʼ�����ϲ�
		Ȼ���ǳ���2�������ϲ�
		�������鳤�Ȳ�һ����2���ݴ�
		����������һ��һС�������2���ݴΣ�С������
		Ȼ���ٶ���һ��һС���кϲ�
*/
void merge_sort(vector<int>& nums, int l, int r)
{
	if (r - l < 2)
	{
		return;
	}

	int mid = (l + r) / 2;
	merge_sort(nums, l, mid);
	merge_sort(nums, mid, r);
	vector<int> tmp = nums;

	//����������ϲ�
	int p1 = l, p2 = mid;
	while (p1 < mid && p2 < r)
	{
		if (nums[p1] < nums[p2])
		{
			tmp[l++] = nums[p1++];
		}
		else
		{
			tmp[l++] = nums[p2++];
		}
	}

	while (p1 < mid)
	{
		tmp[l++] = nums[p1++];
	}

	while (p2 < r)
	{
		tmp[l++] = nums[p2++];
	}

	nums.swap(tmp);
}

void merge_sort(vector<int>& nums)
{
	merge_sort(nums, 0, nums.size());
}

void merge_sort2(vector<int>& nums)
{
	vector<int> tmp = nums;
	int size = nums.size();
	// �������С��1��ʼ��ÿ�η�����ֱ������size
	int i = 1;
	for (; i < size; i *= 2)
	{
		// ÿ������������кϲ�
		for (int j = 0; j < size; j += 2 * i)
		{
			int l = j, r = std::min(j + 2 * i, size);
			int mid = (l + r) >> 1;
			int p1 = l, p2 = mid;
			int start = l;
			while (p1 < mid && p2 < r)
			{
				if (nums[p1] < nums[p2])
				{
					tmp[start++] = nums[p1++];
				}
				else
				{
					tmp[start++] = nums[p2++];
				}
			}

			while (p1 < mid)
			{
				tmp[start++] = nums[p1++];
			}

			while (p2 < r)
			{
				tmp[start++] = nums[p2++];
			}
		}
		nums.swap(tmp);
	}

	// ���һ�η��飬���ܻ���һ��һС�����i�Ѿ�������size��������ִ��һ�κϲ�
	int l = 0, r = size;
	int mid = i / 2;
	int p1 = l, p2 = mid;
	int start = l;
	while (p1 < mid && p2 < r)
	{
		if (nums[p1] < nums[p2])
		{
			tmp[start++] = nums[p1++];
		}
		else
		{
			tmp[start++] = nums[p2++];
		}
	}

	while (p1 < mid)
	{
		tmp[start++] = nums[p1++];
	}

	while (p2 < r)
	{
		tmp[start++] = nums[p2++];
	}

	nums.swap(tmp);
}

void heap_sort(vector<int>& nums)
{
	int size = nums.size();

	//// �ȶ����鹹���󶥶ѣ���ǰ�����ÿ��Ԫ���ϸ�
	//for (int i = 1;i < size;++i)
	//{
	//	int n = i;
	//	while (nums[(n - 1) / 2] < nums[n] && n > 0)
	//	{
	//		std::swap(nums[n], nums[(n - 1) / 2]);
	//		n = (n - 1) / 2;
	//	}
	//}

	// �����󶥶��Ż��������һ����Ҷ�ӽڵ㿪ʼ�³�
	// ��ΪֻҪ�����Ӷ��Ǵ󶥶ѣ����Լ��³����ܵõ��󶥶ѣ�����Ӧ�ôӺ���ǰ��������Ҷ�ӽڵ�û�������Ӷѣ������Ǵ����һ����Ҷ�ӽڵ㿪ʼ
	// ����������i+1�У����һ�еĽڵ���Ϊk�������ڶ��ڵ�Ϊ2^(i-1)�����ܹ���2^i-1+k���ڵ�
	// Ҷ�ӽڵ���k+ 2^(i-1) - (k+1)/2 = (2k+2^i-k-1)/2 = (2^i+k-1)/2 �����պ����ܽڵ�����һ��
	// ���ߣ����һ���ڵ���size-1�����ĸ��ڵ�һ�������һ����Ҷ�ӽڵ㣬�� (size-1 - 1)/2 = size/2 - 1
	for (int i = size / 2 - 1;i >=0; --i)
	{
		int n = i;
		while (2 * n + 2 < size || 2 * n + 1 < size)
		{
			int max = n;
			if (2 * n + 1 < size && nums[max] < nums[2 * n + 1]) max = 2 * n + 1;

			if (2 * n + 2 < size && nums[max] < nums[2 * n + 2]) max = 2 * n + 2;

			if (max == n) break;

			std::swap(nums[n], nums[max]);
			n = max;
		}
	}

	// ���׸�Ԫ�غ�ĩβ������Ȼ�����Ԫ���³�
	// ����Ԫ�طŵ���ĩβ��Ȼ���ٴε����󶥶�ʹʣ�µ����Ԫ�ط��ڶѶ����ȴ���һ�λ������ظ�size-1��
	for (int i = size - 1; i >= 0; --i)
	{
		std::swap(nums[i], nums[0]);
		int n = 0;
		while (2 * n + 2 < i || 2 * n + 1  < i)
		{
			int max = n;
			if (2 * n + 1 < i && nums[max] < nums[2 * n + 1]) max = 2 * n + 1;

			if (2 * n + 2 < i && nums[max] < nums[2 * n + 2]) max = 2 * n + 2;
			
			if (max == n) break;

			std::swap(nums[n], nums[max]);
			n = max;
		}
	}
}