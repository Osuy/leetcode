#include"56.合并区间.h"
#include "排序.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Solution obj{};
	vector<vector<int>>matrix
	{
		{1,3},
		{2,6},
		{8,10},
		{15,18}
	};

	vector<int> arr{ 110,100,0, 9, 43, 67,88,4,12 };
	qsort(arr);
	
	obj.merge(matrix);
	return 0;
}