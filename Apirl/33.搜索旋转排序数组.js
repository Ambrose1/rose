/*
 * @lc app=leetcode.cn id=33 lang=javascript
 *
 * [33] 搜索旋转排序数组
 */

// @lc code=start
/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var search = function(nums, target) {
    if (nums.length === 0) {
        return -1;
    }
    if (nums.length === 1){
        return nums[0] === target ? 0 : -1;
    }
    let st = 0,end = nums.length-1;
    while(st<=end){
        let mid = (st+end) >> 1;
        if (nums[mid] === target) {
            return mid;
        }
        if(nums[st] <= nums[mid]) {
            // 左侧有序
            if(target < nums[mid] && target >= nums[st]){
                end = mid -1;
            }else {
                st = mid +1;
            }
        } else {
            // 右侧有序
            if(target > nums[mid] && target <= nums[end]) {
                st = mid +1;
            }else {
                end = mid -1;
            }
        }
    }
    return -1;
};
// @lc code=end

