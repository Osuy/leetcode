#pragma once
#include "../base_header.h"
#include "TreeNode.h"
/*
	�Ѷȣ��е�
	������������ĳ�����еĽڵ㣬��K
	������������о�������ڵ�ΪK�Ľڵ�
	�������ǵ�Ԫ��ֵ����


	���Կ�������bfs�����ǴӸ��ڵ���������������ĳ���ڵ㿪ʼ
	���ڽڵ�û�����丸�ڵ��������������һ��ջ��������ڵ㵽�ýڵ��·��
	ÿ�γ�ջ���൱�ھ���+1��ͬʱ��ջ��Ԫ�ص���һ�������ǿ��Բ�������ģ�Ҫ���뵽������
*/

class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ans;
        if (0 == k)
        {
            // ���ڷֱ��ö��к�ջ������������µľ���k�Ľڵ�
            // ���kΪ0���������������Ρ�û�кܺõİ취ȥ��������ֱ�����⴦��
            ans.push_back(target->val);
            return ans;
        }

        // �ݹ��ҵ�target����·������ջ
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
        auto top = target;// ջ����Ҫ���ջ���Ƚϣ�������ǰ��top��������
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
                // ��ջ����ջ������������ջ������һ���������뵽����
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
                if (0 == k) // ��ջ��ջ������target = ѭ���������������Ϊk���Ǵ�֮һ
                {
                    ans.push_back(top->val);
                }
            }

            --k;
        }

        return ans;
    }
};