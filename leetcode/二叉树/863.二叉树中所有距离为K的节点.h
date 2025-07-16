#pragma once
#include "../base_header.h"
#include "TreeNode.h"
/*
	难度：中等
	给出二叉树、某个树中的节点，和K
	求二叉树中所有距离这个节点为K的节点
	返回它们的元素值数组


	可以看作异形bfs，不是从根节点层序遍历，而是由某个节点开始
	由于节点没法向其父节点遍历，所以利用一个栈来保存根节点到该节点的路径
	每次出栈，相当于距离+1，同时，栈顶元素的另一个子树是可以层序遍历的，要加入到队列中
*/

class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ans;
        if (0 == k)
        {
            // 由于分别用队列和栈计算两种情况下的距离k的节点
            // 如果k为0，则会把起点计入两次。没有很好的办法去除，所以直接特殊处理
            ans.push_back(target->val);
            return ans;
        }

        // 递归找到target，把路径存入栈
        stack<TreeNode*> st;
        auto recursion = [&st, target](this auto&& recursion, TreeNode* node)
            {
                if (!node)return;
                if (!st.empty() && st.top() == target)return;
                st.push(node);
                if (st.top() == target)return;
                recursion(node->left);
                if (st.top() == target)return;
                recursion(node->right);
                if (st.top() == target)return;
                st.pop();
            };

        recursion(root);

        queue<TreeNode*>q;
        q.push(target);
        auto top = target;// 栈顶需要与旧栈顶比较，所以提前用top变量保存
        while (!q.empty() || !st.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; ++i)
            {
                auto node = q.front();
                q.pop();

                if (!node)continue;

                if (0 == k)
                {
                    ans.push_back(node->val);
                    continue;
                }
                q.push(node->left);
                q.push(node->right);
            }

            if (!st.empty())
            {
                // 旧栈顶是栈顶的子树，把栈顶的另一个子树加入到队列
                if (top == st.top()->left)
                {
                    q.push(st.top()->right);
                }
                else if (top == st.top()->right)
                {
                    q.push(st.top()->left);
                }

                top = st.top();
                st.pop();
                if (0 == k) // 出栈后，栈顶距离target = 循环次数，所以如果为k就是答案之一
                {
                    ans.push_back(top->val);
                }
            }

            --k;
        }

        return ans;
    }
};