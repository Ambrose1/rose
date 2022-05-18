
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
 

class Solution {
public:
    /**
     * 
     * @param root TreeNode类 
     * @param sum int整型 
     * @return bool布尔型
     */
    bool hasPathSum(TreeNode* root, int sum) {
        // write code here
       if(!root){
           return false;
       }
        return dfs(root,sum);
    }
    
    bool dfs(TreeNode* root, int target) {
        if(!root)return false;
        target-= root->val;
        if(!root->left && !root->right && target==0)return true;
        
        return dfs(root->left,target) || dfs(root->right, target);
    }
};