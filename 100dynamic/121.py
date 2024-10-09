class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [[0]*3 for _ in range(n)]
        dp[0][0] = -prices[0]
        dp[0][1] = 0
        dp[0][2] = 0

        for i in range(1,n):
            dp[i][0] = max(dp[i-1][0],-prices[i])
            dp[i][1] = prices[i] + dp[i-1][0]
            dp[i][2] = max(dp[i-1][1], dp[i-1][2])
        return dp[n-1][1] if dp[n-1][1] > dp[n-1][2] else dp[n-1][2]
