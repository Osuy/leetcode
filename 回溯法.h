#pragma once
#include <vector>
using std::vector;
/*
	���/�Ӽ�
		��������ѡȡ����Ԫ�أ�ѡȡ��˳���޹�
		���ѡȡԪ�أ�ֱ�������ڵ�Ԫ�ش��ĳ����
		����������������ѡȡ��ʽ
		�Ӽ�/������ڲ�����˳�����������0��ʼ�����ᷢ���ظ���
			ѡ��i��ѡ��j
			ѡ��j��ѡ��i
		������Ϊ��ͬ�ļ���
		���ǵ�i��Ԫ�أ�Ϊ�������а���i���Ӽ�����i���룬Ȼ��ȥ����δ���ǵ�Ԫ�أ������Ԫ�أ�
		��ĳ��ѡ��Ԫ��i����һ��ѡ��Ҫ��i+1��ʼ
		��ѡ������Խ��Խ�ٵ�

	����
		ѡȡ����Ԫ�أ�ѡȡ��˳���йأ�����һ��Ҫ��̶�����
		���ѡȡԪ�أ�ֱ�����ȴﵽĳֵ
		����Ҫ��ѡȡ˳���ظ���������˳��
		����˳��ͬ��Ϊ��ͬ�����У����Զ��ڣ�
			ѡ��i��ѡ��j
			ѡ��j��ѡ��i
		��Ϊ���ֲ�ͬ�����У���Ҫ���ǣ��������ĵݹ���
		ĳ��ѡ��i����һ����Ȼ��0��ʼ�����Ǵ���iҲ����ʡ���ˣ�������Ҫ������ѡ��Ԫ��
		���Ծ���Ҫ��used������ά������Ԫ�ص�ʹ�����
		���Ӽ�/��ϲ�������Ϊi����һ���i+1��ʼ����Ȼ��δʹ�ù��ģ�

	
	�����Ƕ��ڣ�Ԫ�����ظ����ɸ�ѡ����Ŀ��ͨ�ýⷨ������Ҫע�����ֱ��壺
		Ԫ�ؿ��ظ����ɸ�ѡ
		Ԫ�����ظ��ɸ�ѡ
	Ϊʲôû�п��ظ��ɸ�ѡ����Ϊĳ��Ԫ�ؿɸ�ѡ���������ظ��ģ���ô���۸�ѡ�Ǹ���һ��
	Ҳ�Ϳ���ֱ��ȥ�أ�������ת��δ���ظ��ɸ�ѡ

	��ϣ�Ԫ�ؿ��ظ����ɸ�ѡ
		��Ϊ��Ԫ���ظ������/�Ӽ����һ���־ͻ��ظ�
		��ĳ�����Ӽ�����������Ԫ��һ����һ��ѡ��i��һ��ѡ��i'�����Ǳ���Ϊͬһ���Ӽ������޳���
		Ȼ������֪����i��ȵ�Ԫ��i'�����������Ҫ��������������
		Ȼ����ѡȡʱ��������������ͬ��Ԫ�أ�ֻѡ��һ��
		�����Ҫ������ͬ�ģ�������Ե�һ�������һ�������Ǵ˴������һ��
		����Ϊʣ�����ͬԪ�ؿ�������һ�㱻ѡ��ֻ����һ���ѭ��������ѡ��
		�����������ѡ���һ������һ��Ͳ���ѡ������ͬԪ����
		�����磺1223ѡ����Ϊ3���Ӽ������������ͬ��2ѡ���һ�������ֻ��123
		������122��223��ȻҲ�Ǵ𰸣�
		����
			if(j > i && nums[j] == nums[j-1])continue;
			Ϊʲô������j����i���жϣ�
			��Ϊ��һ��Ŀ�ѡ������[i, end)
			j��i��ʼ����������j = iʱ�� i - 1���ǿ�ѡ�����ڵ�Ԫ�أ����������ж��Ƿ��ظ�
			���磬��һ��ѭ��ѡ��i����һ��ѭ��i'�ǿ�ѡ�ġ�����������ж�j>i
			��ô���ж� i��i'���Ȼ������i'
			һ�仰���ӿ�ѡ������ѡ����ͬԪ���еĵ�һ��

	���У�Ԫ�ؿ��ظ����ɸ�ѡ
		��ΪҲҪ������ͬԪ�أ�����Ҳ��Ҫ����
		ĳһ��ѡ��i����used[i] = true����������������ͬ��i'
		��֮ͬ�����ڣ����ں����� i'�ǿ�ѡ�ģ��������� i' == i��i'-1������i'Ҳ�ᱻ����
		����������ʱ���жϲ��ǡ���ǰһ����ͬ�������ǡ���ǰһ��δ�ù�����ͬ��
		�����ǣ���0��ʼѭ����used���������еĺ��ģ�
		���Ǿ�Ҫд�ɣ�
			if(j > 0 && nums[j] == nums[j-1] && ��used[j-1])continue;
			j>0ֻ��Ϊ�˱�֤j-1Ҳ����Ч�����������岻��
			!used[j-1]�����������ų� ��ʹ�õ���ͬԪ��
			һ�仰����δʹ��Ԫ����ѡ����ͬԪ�صĵ�һ��

	��ϣ����ظ��ɸ�ѡ
		�Ӽ�/�����ͨ������i�����һ�����i+1�ﵽ����ѡ��Ч����
		����Ȼ�ɸ�ѡ��ֻҪ��һ����Ȼ��i��ʼ�������ɡ�
		Ϊʲô���Ǵ�0��ʼ��
		��Ϊ������ÿһ������������i�ļ��ϣ�����˵���󲻰���[0~i-1]�ļ���
		��Ϊǰ��Ĳ��Ѿ�������[0~i-1]�ˡ�����һ��>�Ĳ���������������<=
		�����i+1��ʼ������һ�㣬����<�����ɸ�ѡ����<=
		���j��i��ʼ�����Ϳ���ʵ�ָ�ѡ
		��Ϊ�ɸ�ѡ�����Ե�����������ȥ����˿ɸ�ѡ����Ŀ������ʩ�����ƣ��糤�ȡ��ܺ�

		�����������⣬�������ѡ����ô���ò���used���飬n��Ԫ�ص����о���n^n��

	�ܽ᣺
		�Ӽ�/������⣬ÿ�����δ������Ԫ�أ����Եݹ鴫i+1�����Ԫ�����ظ�������Ȼ��������һ������ظ���
			���ѡȡ���ظ�����ݹ鴫i��ʹ��һ������ѡ��i

		�������⣬ÿ�����δʹ��Ԫ�أ�������Ҫused�����¼ʹ����������Ԫ�����ظ�������Ȼ������δʹ�õ��ظ���
			���ѡȡ���ظ����������¼used
*/


/*
	��1��46ȫ����
	�������ظ������Բ�������
	ÿ��ѭ����0��ʼ
*/

vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int>> ans;
	vector<int> permutation;
	vector<bool> used(nums.size(), false);
	auto dfs = [&](this auto&& dfs)
		{
			if (permutation.size() == nums.size())
			{
				ans.push_back(permutation);
				return;
			}
			for (int i = 0; i < nums.size(); ++i)
			{
				if (used[i])continue;
				permutation.push_back(nums[i]);
				used[i] = true;
				dfs();
				permutation.pop_back();
				used[i] = false;
			}
		};

	dfs();

	return ans;
}

/*
	��2��77���
	���ظ������ɸ�ѡ��ÿ��ѭ����������С����
*/
vector<vector<int>> combine(int n, int k) {
	vector<vector<int>> ans;
	vector<int> combination;
	auto dfs = [&](this auto&& dfs, int i)
		{
			if (combination.size() == k)
			{
				ans.push_back(combination);
				return;
			}

			for (int j = i; j <= n; ++j)
			{
				combination.push_back(j);
				dfs(j + 1);
				combination.pop_back();
			}
		};

	dfs(1);
	return ans;
}

/*
	��3��78�Ӽ�
	������������Ӽ��������Ӽ���Ԫ�������ǿ���С������ģ����һ������ǿ�
	������ѡԪ�ص����п��ܶ���һ���Ӽ�
	�������賤�ȴﵽsize���ռ��𰸣����Ƕ�ÿ����ѡ���϶��ռ���
*/

vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> ans;
	vector<int> subset;
	auto dfs = [&](this auto&& dfs, int i) -> void
		{
			ans.push_back(subset); // ÿ��ѡ��ǰ��������ans

			for (int j = i; j < nums.size(); ++j)
			{
				subset.push_back(nums[j]);
				dfs(j + 1);
				subset.pop_back();
			}
		};

	dfs(0);
	return ans;
}

/*
	��4��47ȫ����2
	����Ԫ�ؿ����ظ�
	Ϊ���������ظ���Ҫ�������飬ʹ�ظ�Ԫ������
	����������ʹ�õ�Ԫ����
	��Ҫ������ǰһ����ͬ��ǰһ��δʹ�õ�Ԫ�أ��������ܴ��ȥ������
	��һ��ѭ��ֻ��ѡȡһ��Ԫ�أ�Ҳ����һ��Ԫ�ػᱻ���Ϊ��ʹ�ã����ǰһ��Ԫ������ʹ�õĻ�
	˵������һ��ѭ���ģ���Ӱ�죩
*/

vector<vector<int>> permuteUnique(vector<int>& nums) {
	sort(nums.begin(), nums.end());// �������飬ʹ�ظ�Ԫ������
	vector<vector<int>> ans;
	vector<int> permutation;
	vector<bool> used(nums.size(), false);
	auto dfs = [&](this auto&& dfs)
		{
			if (permutation.size() == nums.size())
			{
				ans.push_back(permutation);
				return;
			}
			for (int i = 0; i < nums.size(); ++i)
			{
				if (used[i])continue;
				if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])continue; // ��������һ��Ԫ����ͬ����һ��Ԫ��δʹ�õ�Ԫ��

				permutation.push_back(nums[i]);
				used[i] = true;
				dfs();
				permutation.pop_back();
				used[i] = false;
			}
		};

	dfs();

	return ans;
}

/*
	��5��90�Ӽ�2
	������ظ�Ԫ�ص�������Ӽ�
	����Ȼ����ѭ���������ظ�Ԫ��
	ע��ֻ��������ѡ����������ظ�Ԫ�أ�j-1��������ڿ�ѡ���䣬�������������׸�Ԫ����ͬ�����ǲ�Ӱ��
*/
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	vector<vector<int>> ans;
	vector<int> subset;
	auto dfs = [&](this auto&& dfs, int i) -> void
		{
			ans.push_back(subset);

			for (int j = i; j < nums.size(); ++j)
			{
				if (j > i && nums[j] == nums[j - 1])continue; // �����ظ�Ԫ�ء�Ҫ��֤j - 1 >= i��ʹ��������ʵ��ǿ�ѡ���� 
				subset.push_back(nums[j]);
				dfs(j + 1);
				subset.pop_back();
			}
		};

	dfs(0);
	return ans;
}

/*
	��6��39����ܺ�
		��������ѡȡԪ�أ�ʹ��Ϊĳֵ
		һ��Ԫ�ؿɱ����ѡȡ

	ÿ��ѭ���ĵ�����i��ʼ���Ǵ�i+1��ʼ�����ܿ���Ԫ�صĶ��ѡȡ
*/

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>> ans;
	vector<int> combination;
	int sum = 0;
	auto dfs = [&](this auto&& dfs, int i)
		{
			if (sum == target)
			{
				ans.push_back(combination);
				return;
			}

			if (sum > target)return; // �ͳ���targetҪ�˳������������ѭ��

			for (int j = i; j < candidates.size(); ++j)
			{
				combination.push_back(candidates[j]);
				sum += candidates[j];
				dfs(j); // �²�ѭ����Ȼ��i��ʼ
				combination.pop_back();
				sum -= candidates[j];
			}
		};

	dfs(0);
	return ans;
}