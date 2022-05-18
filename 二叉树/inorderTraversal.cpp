#include<iostream>
#include<vector>
#include<stack>

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

vector<int> inorderTraversal(TreeNode* root) {
        // write code here
        if(root){
            inorderTraversal(root->left);
            ans.push_back(root->val);
            inorderTraversal(root->right);
        }
        return ans;
    }

vector<int> inorderTraversal(TreeNode* root) {
        // write code here
        stack<TreeNode *> st;
        TreeNode *node = root;
        while(!st.empty() || node){
            if(node){
                st.push(node);
                node = node->left;
            }else {
                node = st.top();
                st.pop();
                ans.push_back(node->val);
                node = node->right;
            }
        }
        return ans;
    }
    

};
