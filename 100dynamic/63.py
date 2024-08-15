class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        m,n = len(obstacleGrid), len(obstacleGrid[0])
        dp = [0] * n
        for i in range(n):
            if (obstacleGrid[0][i] == 0):
                dp[i] = 1
            else:
                break
        
        for i in range(1,m):
            for j in range(n):
                if (obstacleGrid[i][j] == 1):
                    dp[j] = 0
                else:
                    if (j > 0):
                        dp[j] += dp[j-1]
        return dp[n-1]
