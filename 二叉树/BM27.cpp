#include<iostream>
#include<vector>
#include<queue>
#include<stack>
//给定一个二叉树，返回该二叉树的之字形层序遍历，（第一层从左向右，下一层从右向左，一直这样交替）

using namespace std;


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 

class Solution {

private:

vector<int> ans;
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        
        vector<vector<int> >  ans;
        vector<int> tmp;
        TreeNode *node = nullptr;
        if(pRoot == nullptr)return ans;
        bool direct = false;
        queue<TreeNode *> qu;
        stack<TreeNode *> st;
        qu.push(pRoot);
        while(!qu.empty()) {
            int n= qu.size();
            for(int i=0; i<n; i++){
                node = qu.front();
                qu.pop();
                tmp.push_back(node->val);
                if(direct){
                    if(node->right)st.push(node->right);
                    if(node->left)st.push(node->left);
                }else {
                    if(node->left)st.push(node->left);
                    if(node->right)st.push(node->right);
                }
            }
            direct = !direct;
            ans.push_back(tmp);
            tmp.clear();
            
            while(!st.empty()){
                qu.push(st.top());
                st.pop();
            }
        }
        return ans;
    }

};
