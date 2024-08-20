class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        @lru_cache(None)
        def dfs(level,index):
            if level == len(triangle) -1:
                return triangle[level][index]
            left = dfs(level + 1, index)
            right = dfs(level + 1, index + 1)

            min_v = triangle[level][index] + min(left, right)
            return min_v
        return dfs(0,0)

class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        def dfs(level,index):
            if level == len(triangle) -1:
                return triangle[level][index]
            if (level,index) in memo:
                return memo[(level,index)]
            left = dfs(level + 1, index)
            right = dfs(level + 1, index + 1)

            min_v = triangle[level][index] + min(left, right)
            memo[(level, index)] = min_path
            return min_v
        memo = {}
        return dfs(0,0)

class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        dp = [0] * n
        dp[0] = triangle[0][0]
        for i in range(1,n):
            dp[i] = dp[i - 1] + triangle[i][i]
            for j in range(i-1,0, -1):
                dp[j] = min(dp[j],dp[j-1]) + triangle[i][j]
            dp[0] += triangle[i][0]
        
        return min(dp)