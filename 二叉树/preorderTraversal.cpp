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
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param root TreeNode类 
     * @return int整型vector
     */
    vector<int> preorderTraversal(TreeNode* root) {
        // write code here
        if(root != nullptr){
            ans.push_back(root->val);
            if(root->left)preorderTraversal(root->left);
            if(root->right)preorderTraversal(root->right);
        }
        return ans;
    }

    // 非递归
    vector<int> preorderTraversalN(TreeNode* root) {
        // write code here
        if(root ==  nullptr)return ans;
        stack<TreeNode *> st;
        st.push(root);
        while(!st.empty()){
            TreeNode *node = st.top();
            st.pop();
            ans.push_back(node->val);
            if(node->right){
                st.push(node->right);
            }
            if(node->left){
                st.push(node->left);
            }
        }
        return ans;
    }

    

}
