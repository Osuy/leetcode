#pragma once
#include "../base_header.h"
/*
	�еȣ����ǻᳬʱ����Ҫ���ñ���¼�Ż���ʵ���Ѷȴﵽ������
	�ж������ܷ񱻷�Ϊk�����ϣ�ÿ�����ϵ�Ԫ�غ����

	���ȣ��������Ԫ�غ��ܷ�k������������ֱ��false
	��������Ϊaverage

	�ⷨ1��ÿ��ݹ���Ԫ��iȥ����k��sum�е�����һ������ѭ�����ȷŽ�0��������һ��ݹ�
	����һ��ݹ鷵�غ󣬴�0��������ٷ���1��������һ��ݹ顣��������
	����һ��ݹ���Ԫ��i+1ѡ�����
	�ýⷨ��ȱ���Ǳ���ͬʱ����k��sum�����ŵݹ��Σ����ǻ����ۼӣ�ֱ������sum��Ϊaverage
	�ж�����sum��Ϊaverage��һ��ѭ����������ʱ�临�Ӷȣ����³�ʱ
	����ص����뵽һ������Ҫѭ�������жϴ𰸵ķ�ʽ

	�ⷨ2��sumȥ�ռ�Ԫ�أ���Ϊÿ��sumû�����𣬶�ֻҪ��Ϊaverage��
	���sum����averrage��˵�����sum���ϣ��е���һ��sumȥ�ռ�
	��sum1�ռ���Ԫ�أ�Ҫ��һ��used����ȥ�����ʹ��
	sum2�Ͳ������ռ���
	�������ݹ鵽��sumk�ռ����ʱ��Ҳ��˵���Ҵ�
	������ѭ����������˵��Ŀǰ���ռ���ϲ����ҵ��𰸣�������һ�㣬��һ��ѭ��������

	������Ȼ�ᳬʱ
	������Ϊ����sum1 �ռ���1��4��sum2�ռ���2��3������û�ҵ���
	�����˻ص���һ�㣬����ѭ����sum1�ռ���2��3��sum2�ռ���1��4
	��Ȼ��������Ѿ���������Ҳ��������ȷ�𰸣������˷�ʱ�����
	��used��¼���ռ�������ϡ������ٰ�used����hash��������
	����ݹ�ʱ������hash�����used������used��ֵΪfalse����˵����ǰused�Ҳ����𰸣�ֱ�ӷ���

*/

bool canPartitionKSubsets(vector<int>& nums, int k) {
	int average = 0;
	for (auto el : nums)average += el;
	if (average % k)return false;
	average /= k;
	bool found = false;

	// �ⷨ1��Ԫ����Ͱ���жϳɹ����ӣ��ᳬʱ
	// vector<int> sum(k, 0);
	// auto dfs = [&](this auto&& dfs, int i)->void
	// {
	//     if(found)return;
	//     if(i==nums.size())
	//     {
	//         for(int index = 0; index < k; ++index)
	//         {
	//             if(sum[index] != average)
	//                 return;
	//         }
	//         found = true;
	//         return;
	//     }

	//     for(int index = 0;index < k; ++index)
	//     {
	//         if(sum[index] + nums[i] > average)continue;

	//         sum[index] += nums[i];
	//         dfs(i+1);
	//         sum[index] -= nums[i];
	//     }
	// };

	// dfs(0);

	// return found;

	unsigned short used = 0;
	unordered_map<unsigned short, bool> useds; // �����Ѿ��ռ�����used���
	auto dfs = [&](this auto&& dfs, int bucket, int i, int start)->bool
		{
			// ʣ��0��Ͱ��˵���ɹ�
			if (i == 0)
			{
				return true;
			}

			// ��Ͱ�Ѿ����ϣ������ݹ���һ��Ͱ
			if (bucket == average)
			{
				useds[used] = dfs(0, i - 1, 0);

				return useds[used];
			}

			// ���used��ʹ�ù���ֱ�ӷ��ر���Ľ��
			if (useds.contains(used))
			{
				return useds[used];
			}

			// ѭ����ѡ��һ��Ԫ�ط���Ͱ�ڣ�������һ��ݹ�
			for (int index = start; index < nums.size(); ++index)
			{
				// �������õ�Ԫ�غ���Ӻ�ᳬ��ƽ��ֵ��Ԫ��
				if (used & (1 << index))continue;
				if (bucket + nums[index] > average)continue;

				bucket += nums[index];
				used |= (1 << index);
				
				if (dfs(bucket, i, index + 1))return true;
				
				used ^= (1 << index);
				bucket -= nums[index];
			}

			return false;
		};

	return dfs(0, k, 0);
}