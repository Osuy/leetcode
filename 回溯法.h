#pragma once
#include <vector>
using std::vector;
/*
	组合/子集
		从数组中选取若干元素，选取的顺序无关
		逐个选取元素，直至数组内的元素达成某条件
		求所有满足条件的选取方式
		子集/组合由于不考虑顺序，所以如果从0开始遍历会发生重复：
			选了i再选了j
			选了j再选了i
		二者视为相同的集合
		考虑第i个元素，为了求所有包含i的子集，将i加入，然后去遍历未考虑的元素（后面的元素）
		即某次选了元素i后，下一层选择要从i+1开始
		可选区间是越来越少的

	排列
		选取若干元素，选取的顺序有关，并且一般要求固定长度
		逐个选取元素，直至长度达到某值
		并且要求选取顺序不重复，求所有顺序
		由于顺序不同视为不同的排列，所以对于：
			选了i再选了j
			选了j再选了i
		视为两种不同的排列，都要考虑，因此排序的递归在
		某层选了i后，下一层依然从0开始（于是传参i也可以省略了），并且要跳过已选的元素
		所以就需要用used数组来维护所有元素的使用情况
		（子集/组合不用是因为i的下一层从i+1开始，自然是未使用过的）

	
	以上是对于：元素无重复不可复选的题目的通用解法，还需要注意两种变体：
		元素可重复不可复选
		元素无重复可复选
	为什么没有可重复可复选？因为某个元素可复选，它又是重复的，那么无论复选那个都一样
	也就可以直接去重，把问题转化未无重复可复选

	组合：元素可重复不可复选
		因为有元素重复，组合/子集里的一部分就会重复
		（某两个子集，其他所有元素一样，一个选了i，一个选了i'，但是被视为同一个子集，需剔除）
		然而并不知道和i相等的元素i'在哪里，于是需要排序，让它们相邻
		然后在选取时，对于相邻且相同的元素，只选第一个
		（如果要跳过相同的，按理可以第一个或最后一个。但是此处必须第一个
		（因为剩余的相同元素可以在下一层被选择，只是这一层的循环不能再选了
		（如果是跳过选最后一个，下一层就不能选不到相同元素了
		（例如：1223选长度为3的子集，如果跳过相同的2选最后一个，则答案只有123
		（但是122和223显然也是答案）
		即：
			if(j > i && nums[j] == nums[j-1])continue;
			为什么还有有j大于i的判断？
			因为这一层的可选区间是[i, end)
			j从i开始遍历，于是j = i时， i - 1不是可选区间内的元素，不能用来判断是否重复
			例如，上一层循环选了i，这一层循环i'是可选的。但是如果不判断j>i
			那么会判断 i和i'相等然后跳过i'
			一句话：从可选区间里选择相同元素中的第一个

	排列：元素可重复不可复选
		因为也要跳过相同元素，所以也需要排序
		某一层选了i，，used[i] = true，并且跳过后续相同的i'
		不同之处在于：对于后续层 i'是可选的，但是由于 i' == i（i'-1）所以i'也会被跳过
		所以在跳过时的判断不是“与前一个相同”，而是“与前一个未用过的相同”
		（谨记：从0开始循环和used数组是排列的核心）
		于是就要写成：
			if(j > 0 && nums[j] == nums[j-1] && ！used[j-1])continue;
			j>0只是为了保证j-1也是有效的索引，含义不多
			!used[j-1]才是真正的排除 已使用的相同元素
			一句话：从未使用元素里选择相同元素的第一个

	组合：无重复可复选
		子集/组合是通过迭代i后的下一层迭代i+1达到不复选的效果的
		而既然可复选，只要下一层仍然从i开始迭代即可。
		为什么不是从0开始？
		因为与其所每一层迭代是求包含i的集合，不如说是求不包含[0~i-1]的集合
		因为前面的层已经包含过[0~i-1]了。这是一个>的操作。反过来就是<=
		如果从i+1开始迭代下一层，就是<。而可复选就是<=
		因此j从i开始迭代就可以实现复选
		因为可复选，所以迭代会无限下去。因此可复选的题目本身还会施加限制，如长度、总和

		对于排列问题，如果可重选，那么就用不到used数组，n个元素的排列就是n^n种

	总结：
		子集/组合问题，每层加入未迭代的元素，所以递归传i+1。如果元素有重复，排序，然后跳过这一层里的重复项
			如果选取可重复，则递归传i，使下一层仍能选到i

		排列问题，每层加入未使用元素，于是需要used数组记录使用情况。如果元素有重复，排序，然后跳过未使用的重复项
			如果选取可重复，则无需记录used
*/


/*
	例1：46全排列
	数组无重复，所以不用排序
	每层循环从0开始
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
	例2：77组合
	无重复，不可复选，每层循环的区间缩小即可
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
	例3：78子集
	求数组的所有子集。由于子集的元素数量是可以小于数组的，而且还可以是空
	所以已选元素的所有可能都是一个子集
	于是无需长度达到size再收集答案，而是对每个已选集合都收集答案
*/

vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> ans;
	vector<int> subset;
	auto dfs = [&](this auto&& dfs, int i) -> void
		{
			ans.push_back(subset); // 每次选择前，都加入ans

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
	例4：47全排列2
	数组元素可以重复
	为了能跳过重复，要排序数组，使重复元素相邻
	除了跳过已使用的元素外
	还要跳过于前一个相同且前一个未使用的元素，这样才能达成去重排列
	（一层循环只会选取一个元素，也就是一个元素会被标记为已使用，如果前一个元素是已使用的化
	说明是上一层循环的，不影响）
*/

vector<vector<int>> permuteUnique(vector<int>& nums) {
	sort(nums.begin(), nums.end());// 排序数组，使重复元素相邻
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
				if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])continue; // 跳过与上一个元素相同且是一个元素未使用的元素

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
	例5：90子集2
	求存在重复元素的数组的子集
	排序，然后在循环里跳过重复元素
	注意只跳过本层选择区间里的重复元素，j-1如果不属于可选区间，它即便与区间首个元素相同，但是不影响
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
				if (j > i && nums[j] == nums[j - 1])continue; // 跳过重复元素。要保证j - 1 >= i，使它不会访问到非可选区间 
				subset.push_back(nums[j]);
				dfs(j + 1);
				subset.pop_back();
			}
		};

	dfs(0);
	return ans;
}

/*
	例6：39组合总和
		从数组中选取元素，使和为某值
		一个元素可被多次选取

	每层循环的迭代从i开始而非从i+1开始，就能控制元素的多次选取
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

			if (sum > target)return; // 和超过target要退出，否则会无限循环

			for (int j = i; j < candidates.size(); ++j)
			{
				combination.push_back(candidates[j]);
				sum += candidates[j];
				dfs(j); // 下层循环依然从i开始
				combination.pop_back();
				sum -= candidates[j];
			}
		};

	dfs(0);
	return ans;
}