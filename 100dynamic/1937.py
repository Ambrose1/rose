class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        m,n = len(points), len(points[0])
        dp = [[0] * n for _ in range(m)]
        for i in range(n):
            dp[0][i] = points[0][i]
        for i in range(1,m):
            for j in range(n):
                tmp = 0
                for k in range(n):
                    v = dp[i-1][k] + points[i][j] - abs(k-j)
                    tmp = max(v, tmp)
                
                dp[i][j] = tmp
        return max(dp[m-1])