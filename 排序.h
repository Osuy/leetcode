#pragma once
#include <vector>
using std::vector;

/*
	选择排序
	最基本的排序。思路是找到未排序区间内最小的元素，和已排序区间末尾的下一个元素互换，已排序区间增大，未排序区间缩小，
	由于未排序区间内的元素发生的互换，所以稳定性差

	即便是对于已经大致有序的数组，由于需要确认未排序区间的最小元素，还是要完整遍历，时间复杂度总是O(n^2)
*/
void select_sort(vector<int>& arr)
{
	int size = arr.size();
	for (int i = 0; i < size - 1; ++i)
	{
		// 找到[i, size)内的最小元素，和i互换
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
	冒泡排序
	优化了稳定性。每次从未排序区间寻找最小元素时，不是和已排序区间末尾的下一个元素互换
	而是将前面的所有未排序元素整体后移，使它们保持稳定
	整体后移，在操作上是：从前往后与每一个元素互换
	因此内循环逆向遍历会更方便

	另一种解释是：从后往前，将每对元素里更小的换到前面，完成一次内循环时，最小的元素就会浮现

	由于只有逆序的元素会互换，大于或等于的元素会整体后移，所以比起选择排序有更好的稳定性
	依然需要知道未排序区间的最小元素，时间复杂度总是O(n^2)
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
	插入排序
	另一种优化。不是将未排序区间内的大于最小元素的部分整体后移
	而是将已排序区间内大于新增元素的部分整体后移。即，将新元素插入到已排序区间内
	由于完全没有操作未排序区间，显然具有稳定性
	另外，对于已经大致有序的数组，插入排序在查找插入位置时会更快完成。最好情况时，时间复杂度为O(n)，最坏时也才和选择、冒泡一样
	兼顾了稳定性和性能。std::sort在元素小于47时就会使用插入排序。

	问：为什么对于在有序区间内寻找新元素的位置不用二分查找？
	答：即便使用了二分查找，还需要后移操作，复杂度仍是O(n^2)，所以不如简化代码
*/
void insert_sort(vector<int>& arr)
{
	int size = arr.size();
	for (int i = 1; i < size; ++i)
	{
		// 保存 arr[i]
		// 已排序区间整体往后已，直至arr[j] <= key
		int key = arr[i];
		int j = i;
		while (0 < j && key < arr[j - 1]) //退出循环时，j>=0
		{
			arr[j] = arr[j - 1];
			--j;
		}

		arr[j] = key;
	}
}

/*
	希尔排序
	对插入排序的优化，实现了O(n^2)到O(nlogn)的突破
	前文提到插入排序利用了已排序区间有序的特征，向其中插入新元素。时间复杂度最好的情况是O(n)
	那假如提前对数组处理，使它整体有序，就能优化插入排序。
	希尔排序的想法是，把数组分为多个组，每个组有两个元素，然后将每个组都调整为小的在前，大的在后
	那要怎么分组呢？是两两一组吗？不是。是将整个数组分为前半部分和后半部分，然后每个部分的元素一一组队
	经过一次“调整”后，就满足总体上大的再后面小的在前面
	而这种“调整”就是插入排序。

	当完成一次上述操作后，分组扩大为两倍，重复操作
	直到分组扩大为N，执行最后一次“调整”，也就是插入排序。得到答案

	但是由于分组了，相同元素分到不同组时可能改变位置，所以失去了稳定性。
*/

void shell_sort(vector<int>& arr)
{
	int size = arr.size();
	int gap = size / 2;

	while (0 < gap)// gap缩小到0退出循环
	{
		for (int i = gap; i < size; ++i)//由指向1改为指向第0个分组的第1个，即gap，但是遍历的依然是整个数组
		{
			int key = arr[i];
			int j = i;
			while (gap <= j && key < arr[j - gap]) // 插入到自己的分组内，即 前n*gap个元素里
			{
				arr[j] = arr[j - gap];
				j -= gap;
			}

			arr[j] = key;
		}

		gap /= 2;// gap缩小
	}
}

/*
	快速排序
	二叉树前序遍历思维
	先取一个基准（为方便直接使用第0个元素，一般要随机取）
	然后将所有小于基准的放到前面，将大于等于基准的放到后面，然后基准放到中间
	之后再对左边子数组和右边子数组重复操作
	每次操作遍历N次，并分为两份重复操作，一共重复logN次操作，所以时间复杂度是O(NlogN)

	因为是原地排序，空间复杂度O(1)
	但是对于（与基准）相同元素，原先在基准前后都可能，但是都会排到基准后面，顺序发生改变
	所以是不稳定的排序
*/
void qsort(vector<int>& nums, int l, int r)
{
	// 区间长度仅为1或边界无效，返回
	if (r - l < 2)return;

	// 定位到front和back
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
	归并排序
	二叉树后续遍历，先将两个子数组排序，然后合并

	迭代法
		先从长度1的数组开始两两合并
		然后是长度2，两两合并
		由于数组长度不一定是2的幂次
		所以最后会有一大一小，大的是2的幂次，小的任意
		然后再对这一大一小进行合并
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

	//将两个区间合并
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
	// 自数组大小从1开始，每次翻倍，直到超过size
	int i = 1;
	for (; i < size; i *= 2)
	{
		// 每两个子数组进行合并
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

	// 最后一次分组，可能会有一大一小两组而i已经超出了size，所以再执行一次合并
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

	//// 先对数组构件大顶堆，从前往后对每个元素上浮
	//for (int i = 1;i < size;++i)
	//{
	//	int n = i;
	//	while (nums[(n - 1) / 2] < nums[n] && n > 0)
	//	{
	//		std::swap(nums[n], nums[(n - 1) / 2]);
	//		n = (n - 1) / 2;
	//	}
	//}

	// 构建大顶堆优化：从最后一个非叶子节点开始下沉
	// 因为只要左右子堆是大顶堆，对自己下沉就能得到大顶堆，于是应该从后往前遍历，而叶子节点没有左右子堆，所以是从最后一个非叶子节点开始
	// 假设二叉堆有i+1行，最后一行的节点数为k，倒数第二节点为2^(i-1)个，总共有2^i-1+k个节点
	// 叶子节点有k+ 2^(i-1) - (k+1)/2 = (2k+2^i-k-1)/2 = (2^i+k-1)/2 个，刚好是总节点数的一半
	// 或者：最后一个节点是size-1，它的父节点一定是最后一个非叶子节点，即 (size-1 - 1)/2 = size/2 - 1
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

	// 将首个元素和末尾互换，然后对首元素下沉
	// 最大的元素放到了末尾，然后再次调整大顶堆使剩下的最大元素放在堆顶，等待下一次互换，重复size-1次
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