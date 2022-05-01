/*
 * @lc app=leetcode.cn id=145 lang=javascript
 *
 * [145] 二叉树的后序遍历
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {number[]}
 */
var number = []
var postorderTraversal = function(root) {
    if(root === null){
        return number;
    }
    postorderTraversal(root.left);
    postorderTraversal(root.right);
    number.push(root.val);
};
// @lc code=end

