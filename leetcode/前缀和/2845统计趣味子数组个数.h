#pragma once
#include "../base_header.h"
/*
    �Ѷȣ��е�
    ��Ŀ������һ�����飬һ��ģ��m��һ������k
    �������ڵ�Ԫ������ el % m == k �� ����n���Ҳ���� n%m==k������������ΪȤζ������
    ͳ�������Ȥζ������ĸ���

    ҪѰ���������Ԫ������������ ���������⵽Ԫ�ص����鱾���޹أ�ֻ�����Ƿ���������
    �������뵽ǰ׺�ͣ���¼����������Ԫ�ظ�������presum[j]  - presum[i-1]�õ�[i,j]�����ڵ�����������Ԫ�صĸ���
    ����presum[j] �������presum[i(x)-1] = presum[j] -k - m^x ����ÿ��i����j����Ȥζ������
    ������Ҫ��¼��  presum % m��
    j����presumʱ����Ϊ��������ҽ磬ȥѰ��  (presum[i] + modulo - k) % modulo �Ƿ���ڣ�������ڣ���𰸼��������
    
    
    �ܽ�
        �ؼ�Ҫ�������䣬Ԫ������һ������������������ǰ׺�ͣ��� ��������������������hash���Ǳ����������Ǳ�����ִ���
        ����j����Ȥζ������i��������ͬ�������� (presum[j]-presum[i]) %m = k
        (presum[j] -k+m) %m = (presum[i])%ms
*/

long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) 
{
    vector<int>presum(nums.size() + 1, 0);
    for (int i = 0;i < nums.size();++i)
    {
        presum[i + 1] = presum[i] + ((k == nums[i] % modulo) ? 1 : 0);
    }

    unordered_map<int, int>map;
    long long  ans = 0;
    for (int i = 0;i < presum.size();++i)
    {
        int key = (presum[i] + modulo - k) % modulo;
        if (map.contains(key))
        {
            ans += map[key];
        }

        map[presum[i] % modulo]++;
    }

    return ans;
}

