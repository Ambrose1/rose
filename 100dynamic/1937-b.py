class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        m,n = len(points), len(points[0])
        f = [0] * n
        for i in range(m):
            g = [0] * n
            b = float("-inf")
            for j in range(n):
                b = max(b, f[j] + j)
                g[j] = max(b + points[i][j] - j, g[j])
            b = float("-inf")
            for j in range(n-1,-1,-1):
                b = max(b, f[j] - j)
                g[j] = max(g[j], b + points[i][j] + j)
            f = g
        return max(f)

        return max(dp[m-1])