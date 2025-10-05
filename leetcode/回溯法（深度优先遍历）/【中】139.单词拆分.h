#pragma once
#include "../base_header.h"
/*
	����һ���ַ�����һ���ֵ�
	���ַ����ܷ����ֵ���ĵ���ƴ��

	����˼·��
		1.�����ֵ䣬�����ǰ�ַ����ɵ���i��Ϊǰ׺�����ȥ����i���ݹ�
		2.����ʣ���ַ�����ǰi���ַ������ǰi����ĸ���ɵ��ַ����������ֵ��У����ȥ���ݹ�

	��1�ֿռ临�Ӷȸ��ͣ�
	��2�ַ�ʽ����hash����٣�ʱ�临�Ӷȸ���
	ʵ�ʱȽϣ��������֦�����߶��ᳬʱ����֦���1�ָ��죬�Ʋ���ֱ����s�ϱȽ�ǰ׺�������ʻ��hash�����

	���ڼ�ȥǰ׺��ʵ���Ͽ���ʹ��string_view �������������ַ������޸�

	���ڳ�ʱ���ֵ���ĵ��ʿ��ܷǳ����ꡣ
	���� a��aaaaa
	����ַ�������ƥ�䣬����˵ݹ�a��һ��aaaaa��ʣ����ַ�����һ���ģ��ͻ�����ظ�����
	����ʹ�ñ���¼���м�֦
*/


bool wordBreak(string s, vector<string>& wordDict) {
	// s��dict�����ݶ����ᱻ�޸ģ�����ʹ��string_view������������
	unordered_set<string_view> dict(wordDict.begin(), wordDict.end());
	unordered_map<string_view, bool>visited;
	auto dfs = [&](this auto&& dfs, string_view current) -> bool 
		{
			if (current.empty())
			{
				return true;
			}

			if (visited.contains(current))
			{
				return visited[current];
			}

			auto ret = false;
			for (int i = 1; i <= current.size(); ++i) 
			{
				if (!dict.contains(string_view{ current.begin(), current.begin() + i }))
				{
					continue;
				}

				if (dfs(string_view{ current.begin() + i, current.end() }))
				{
					ret = true;
					break;
				}
			}

			visited[current] = ret;
			return ret;
		};

	return dfs(s);
}