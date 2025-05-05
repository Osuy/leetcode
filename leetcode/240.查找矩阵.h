#pragma once
#include "base_header.h"
/*
	�Ѷȣ��е�
	���Ҿ������Ƿ����target

	��378���Ҿ����ڵ�kС�������ơ�ֻ�����������ֻ������һ�����ߺ���
	�����������ǵĺ�������һ�£�������target��return true

	���岽���ǣ������½ǿ�ʼ�Ҹ��е�һ��������target����val���������target������
	����ƽ�Ƶ���һ��
	��˱�����һ��·��������·�����ɵ����Ͻ��ڵ�Ԫ�ض���С��target�ģ���targetҪô�����ڣ�Ҫô����������·����
*/

bool searchMatrix(vector<vector<int>>& matrix, int target) {
	int x = 0;
	int y = matrix.size() - 1;
	while (x < matrix[0].size())
	{
		while (y >= 0 && matrix[y][x] > target)
		{
			--y;
		}
		if (y >= 0 && target == matrix[y][x])return true;
		++x;
	}

	return false;
}