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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> arr;
        pathSum0(root,targetSum,0,ans,arr);
        return ans;
    }

    void pathSum0(TreeNode* root, int targetSum, int cur, vector<vector<int>> &ans, vector<int> arr){
        if(!root)return ;
        arr.push_back(root->val);
        if(root->left == nullptr && root->right == nullptr){
            if(cur+root->val == targetSum){
                vector<int> tmp(arr);
                ans.push_back(tmp);
            }
            return;
        }
        pathSum0(root->left, targetSum, cur+root->val,ans,arr);
        pathSum0(root->right, targetSum, cur+root->val,ans, arr);
    }
};