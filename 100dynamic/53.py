class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        if (n == 1):
            return nums[0]
        tmp = nums[0]
        res = tmp
        for i in range(1,n):
            tmp = max(tmp + nums[i], nums[i])
            if tmp > res:
                res = tmp
        return res
