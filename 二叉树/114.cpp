#include<iostream>
#include<vector>
// #include<queue>
// #include<stack>
using namespace std;
/**
 * Definition for a binary tree node.
 * */
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


class Solution {
public:
    void flatten(TreeNode* root) {
        dfs(root);
    }

    void dfs(TreeNode* root){
        if(!root){
            return;
        }
        TreeNode* left = nullptr, *right = nullptr;

        if(root->left){
            left = root->left;
            root->left = nullptr;
            dfs(left);
        }
        if(root->right){
            right = root->right;
            dfs(right);
        }
        if(left && right){
            root->right = left;
            while(left->right)left=left->right;
            left->right = right;
        } else if(left) {
            root->right = left;
        } else if(right){
            root->right = right;
        }
    }
};