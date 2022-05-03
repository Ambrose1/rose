/*
 * @lc app=leetcode.cn id=137 lang=javascript
 *
 * [137] 只出现一次的数字 II
 */

// @lc code=start
/**
 * @param {number[]} nums
 * @return {number}
 */
var singleNumber = function(nums) {
    if (nums.length <= 0)return;
    var dic = {}
    const n = nums.length;
    let ans = nums[0]
    for(let i=0;i<n;i++){
        if(nums[i] in dic){
            dic[nums[i]]++;
        } else {
            dic[nums[i]] = 1
        }
    }
    for(let key in dic){
        if(dic[key] == 1){
            return key;
        }
    }
};
// @lc code=end

