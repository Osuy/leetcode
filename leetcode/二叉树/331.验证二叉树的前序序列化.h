#pragma once
#include "../base_header.h"
/*
	难度：中等
	规定二叉树的前序遍历字符串为：每个元素间由','隔开，空节点为'#'
	判断一个字符串是否是有效的二叉树前序遍历

	由于是前序遍历，所以第一个元素是根节点，第二个元素是左子树的根节点
	但是右子树的位置并不知道
	可以递归地去遍历左子树，并让其返回树的长度，从而确定右子树根节点的位置
	如果遇到'#'则直接返回1，如果空或者非'#'但是长度小于5（叶子节点至少是： "X，#，#"，长度为5），则字符串无效
*/

bool isValidSerialization(string preorder) {
	bool ans = true;
	auto recursion = [&ans](this auto&& recursion, string_view str)->int
		{
			if (!ans)return 0; // 已经无效，无需继续
			auto i = str.find(',');
			if (string::npos == i)
			{
				i = str.size();
			}

			if ("#" == str.substr(0, i))
			{
				return 1;
			}

			if (str.size() < 5)
			{
				ans = false;
				return 0;
			}

			// 得到左子树的长度，然后确定右子树的起点，递归右子树
			auto left_size = recursion(str.substr(i + 1));
			auto right_size = recursion(str.substr(1 + i + left_size + 1));
			// 返回 i + 1 + left_size + 1 + right_size 
			return i + 1 + left_size + 1 + right_size;
		};

	return recursion(preorder) == preorder.size() && ans;
}

/*
	数学解法（无需二分递归）
	如果一个节点有子节点，则认为其产生了指向子节点的边
	子节点消耗了来自父节点的边，数量上相同
	对于空节点，其只消耗边不产生边，对于根节点，只产生边不消耗边
	如果某一时刻消耗的边更多，则错误
	算法结束后，如果edge==0则true
*/

bool isValidSerialization(string preorder) {
	int edge = 1;
	stringstream ss{ preorder };
	string node;
	while (getline(ss, node, ','))
	{
		--edge;
		if (edge < 0)return false;
		if (node != "#")
		{
			edge += 2;
		}
	}

	return 0 == edge;
}