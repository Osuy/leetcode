#include  "base_header.h"

namespace q105
{
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};

TreeNode* build(span<int> preorder, span<int> inorder) {
	if (preorder.empty())
	{
		return nullptr;
	}

	auto node = new TreeNode{ preorder[0] };
	auto it = find(inorder.begin(), inorder.end(), preorder[0]);
	if (it != inorder.end())
	{
		int index = it - inorder.begin();

		node->left = build(
			span<int>{ preorder.begin() + 1, preorder.begin() + 1 + index },
			span<int>{ inorder.begin(), inorder.begin() + index });

		node->right = build(
			span<int>{preorder.begin() + 1 + index, preorder.end() },
			span<int>{inorder.begin() + 1 + index, inorder.end() });
	}
	return node;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	return build(preorder, inorder);
}


void test()
{
	vector<int> preorder{ 3,9,20,15,7 };
	vector<int> inorder{ 9, 3, 15, 20, 7 };
	buildTree(preorder, inorder);
}
}

