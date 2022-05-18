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

vector<int> postorderTraversal(TreeNode* root) {
    // write code here
    if(root){
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        ans.push_back(root->val);
    }
    return ans;
}

vector<int> postorderTraversal(TreeNode* root) {
    // write code here
    stack<TreeNode*> st;
    TreeNode* node = root;
    TreeNode* last = new TreeNode(0);
    while(!st.empty() || node){
        if(node){
            st.push(node);
            node=node->left;
        }else {
            node = st.top();
            if(node->right && node->right != last){
                node = node->right;
            }else {
                st.pop();
                ans.push_back(node->val);
                last = node;
                node = NULL;
            }
        }
    }
    return ans;
}



};
