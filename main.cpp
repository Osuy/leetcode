//#include"56.合并区间.h"
#include "排序.h"
#include "2132.邮票铺满网格.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Solution obj{};
	vector<vector<int>>matrix
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};

	vector<int> arr{ 110,100,0, 9, 43, 67,88,4,12 };
	shell_sort(arr);
	
	obj.possibleToStamp(matrix,  2, 2);
	return 0;
}