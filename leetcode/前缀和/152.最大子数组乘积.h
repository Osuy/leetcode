#pragma once
#include "../base_header.h"
/*
	�Ѷȣ��е�
	������53����������ʹ�ö�̬�滮����Ϊ��̬�滮�����������˻�������������������ܵõ�����
	���Կ���ʹ��ǰ׺�͵ı��壬ǰ׺�˻�

	ǰ׺��Ϊ��ʱ������ֱ�Ӻ�ansȡ���ֵ����Ϊ������Ȼ�����κδ���1���������С�����Բ����������Ϊ����1��preProduct[0]��
	ǰ׺��Ϊ��ʱ����Ҫ�������ĸ���ǰ׺������Ϊ��������һ��������õ�������Ϊ�˾����ܴ���Ҫ���������������ܴ�
	��һ������ά��ǰ׺�˻�����һ������ά����С����ǰ׺������ʼΪ1��

	ע��ǰ׺����Ҫ����Ԫ��Ϊ0�����⣬����0��������ǰ׺����Ϊ0
	����취������0�������¿�ʼ����ǰ׺��
*/

int maxProduct(vector<int>& nums) {
	int minn = 1;// ��С����ǰ׺������ʼΪ0
	int preproduct = 1;// ǰ׺��
	int ans = INT_MIN;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (0 == nums[i]) // ����0�������������ñ���
		{
			minn = 1;
			preproduct = 1;
			ans = max(ans, 0);// ���ڴ���0�����Դ�����Ϊ0
			continue;
		}

		preproduct *= nums[i];
		if (preproduct < 0)
		{
			ans = max(ans, preproduct / minn);
			minn = minn < 0 ? max(minn, preproduct) : preproduct;
		}
		else
		{
			ans = max(ans, preproduct);
		}
	}

	return ans;
}