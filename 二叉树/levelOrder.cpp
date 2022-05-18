#include<iostream>
#include<vector>
#include<queue>

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

   vector<vector<int> > levelOrder(TreeNode* root) {
    // write code here
    vector<vector<int>> ans;
    queue<TreeNode*> qu;
    qu.push(root);
    TreeNode* node = nullptr;
    while(!qu.empty()){
        vector<int> tmp;
        int n = qu.size();
        for(int i=0; i < n; i++){
            node = qu.front();
            qu.pop();
            tmp.push_back(node->val);
            if(node->left)qu.push(node->left);
            if(node->right)qu.push(node->right);
        }
        ans.push_back(tmp);
    }
    return ans;
}

};
