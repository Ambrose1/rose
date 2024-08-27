class Solution:
    def numberOfWays(self, n: int, x: int) -> int:
        m = 1
        msd = 10**9+7
        for i in range(1,n + 1):
            if i ** x >= n:
                m = i
                break
        dp = [[0] * (n+1) for _ in range(m+1)]
        dp[0][0] = 1
        for i in range(1,m+1):
            power = i ** x
            for j in range(n+1):
                if j < power:
                    dp[i][j] = dp[i-1][j]
                else:
                    dp[i][j] = (dp[i-1][j] + dp[i-1][j-power]) % msd

        return dp[m][n]

