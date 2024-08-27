class Solution:
    def minNum(self, x,y,z):
        tmp = min(x,y)
        return min(tmp,z)
    def minFallingPathSum(self, matrix: List[List[int]]) -> int:
        n = len(matrix)
        dp = [0] * n

        for i in range(n):
            dp[i] = matrix[0][i]
        last = dp[:]
        for i in range(1,n):
            for j in range(n):
                if (j == 0):
                    dp[j] = min(last[j],last[j+1]) + matrix[i][j]
                elif (j == n-1):
                    dp[j] = min(last[j],last[j-1]) + matrix[i][j]
                else:
                    dp[j] = self.minNum(last[j],last[j-1],last[j+1]) + matrix[i][j]
            last = dp[:]
        return min(dp)