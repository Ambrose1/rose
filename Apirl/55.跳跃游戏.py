#
# @lc app=leetcode.cn id=55 lang=python3
#
# [55] 跳跃游戏
#

# @lc code=start
class Solution:
    def canJump(self, nums: List[int]) -> bool:
        if len(nums) == 1:
            return True
        if nums[0] == 0:
            return False
        target = len(nums)-1
        maxnum = 0
        for i in range(len(nums)-1):
            if i<=maxnum:
                maxnum = max(i+nums[i], maxnum)
                if maxnum >= target:
                    return True
        return False
# @lc code=end

