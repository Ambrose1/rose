class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        total = sum(nums)
        if total % 2 != 0:
            return False
        cap,n = total // 2, len(nums)
        dp = [[False] * (cap + 1) for _ in range(n)]
        if max(nums) > cap:
            return False
        dp[0][nums[0]] = True
        for i in range(n):
            dp[i][0] = True
        for i in range(1,n):
            tmp = nums[i]
            for j in range(1,cap+1):
                if j >= tmp:
                    dp[i][j] = dp[i-1][j] or dp[i-1][j-tmp]
                else:
                    dp[i][j] = dp[i-1][j]
        return dp[n-1][cap]
