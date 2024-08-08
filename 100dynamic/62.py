class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [0] * (n)
        dp[0] = 1
        for i in range(0, m):
            for j in range(1, n):
                dp[j] = dp[j-1] + dp[j]
        return dp[-1]