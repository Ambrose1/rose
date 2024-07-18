class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        dp0, dp1 = 0,0

        for i in range(2, len(cost)+1):
            dp = min(dp0 + cost[i-2], dp1 + cost[i-1])
            dp0 = dp1
            dp1 = dp
        return dp1
        