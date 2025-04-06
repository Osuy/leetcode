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
	然后又要满足整体上小的在前大的在后。分组应该是0和N/2一组，1和N/2+1一组。。。。
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