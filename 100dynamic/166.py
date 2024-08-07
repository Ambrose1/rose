class Solution:
    def jewelleryValue(self, frame):
        cols,rows = len(frame), len(frame[0])
        dp = [[0 for _ in range(rows)] for _ in range(cols)]
        print(dp)
        dp[0][0] = frame[0][0]
        print(dp)
        for i in range(1,cols):
            dp[i][0] = dp[i-1][0] + frame[i][0]
        for i in range(1,rows):
            dp[0][i] = dp[0][i-1] + frame[0][i]
        print(dp)
        for i in range(1,cols):
            for j in range(1, rows):
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + frame[i][j]
        print(dp)
        return dp[cols-1][rows -1]
s = Solution()
s.jewelleryValue([[1,3,1],[1,5,1],[4,2,1]])


class Solution:
    def jewelleryValue(self, frame: List[List[int]]) -> int:
        m, n = len(frame), len(frame[0])
        dp = [0] * (n + 1)
        for i in range(0, m):
           for j in range(1, n+1):
                dp[j] = max(dp[j-1], dp[j]) + frame[i][j-1]
        return dp[-1]