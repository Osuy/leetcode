#pragma once
#include <vector>
using std::vector;
/*
	��ʹ��ڵ���target�����������С����
	
	�Ѷȣ��е�

	�������������ģ������뵽�û������ڡ������Ǻʹ��ڵ���target�������ۼӼ���ó���
	����ֻ����ͬ��˫ָ��
	�ҽ�ǰ������������ڵ���target����ans = min(ans, r-l). Ȼ�����ǰ����ֱ����С��target�����ҽ�����

	�ҽ�ǰ��������ĩβʱ����һ��ѭ��Ҫô�ͻ���С��target��Ҫô�����£��
		����������û����Ԫ�أ��Ͳ����ٱ���ˣ�����ѭ���˳�������ʱ�ҽ絽��ĩβ

	���ƵĻ���713 3
*/

class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		int ans = 1e5 + 1;
		int sum = 0;
		int size = nums.size();
		int l = 0, r = 0;// ����ҿ����䣬������ĳ��� = r - l.���ü�1
		while (r < size)
		{
			sum += nums[r++];
			while (l < r && sum >= target)
			{
				ans = std::min(ans, r - l);
				sum -= nums[l++];
			}
		}

		return ans == 1e5 + 1 ? 0 : ans;
	}
};