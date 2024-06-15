class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        m = max(nums)
        diff = [0] * (m + 2)
        for x in nums:
            diff[max(x-k, 0)] += 1
            diff[min(x + k + 1, m + 1)] -= 1
        res, count= 0, 0
        for x in diff:
            count += x
            res = max(res, count)
        return res