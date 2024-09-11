class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        x = min(baseCosts)
        if x > target:
            return x
        can = [False] * (target + 1)
        ans = 2*target - x

        for i in baseCosts:
            if (i <= target):
                can[i] = True
            else:
                ans = min(ans,i)
        for i in toppingCosts:
            for j in range(2):
                for k in range(target, 0, -1):
                    if can[k] and k + i > target:
                        ans = min(ans, k+i)
                    if k - i > 0 and not can[k]:
                        can[k] = can[k-i]
        for i in range(ans - target + 1):
            if (can[target - i]):
                return target - i
        return ans

        n = len(toppingCosts)
        res = 10001
        for i in range(len(baseCosts)):
            total = target - baseCosts[i]
            if total < 0:
                continue
            dp = [[0] * (total + 1) for _ in range(n+1)]
            dp[0][0] = 1
            for j in range(n):
                for k in range(total + 1):
                    if (k >= toppingCosts[j]):
                        dp[j+1][k] = max(dp[j][k],dp[j][k-toppingCosts[j]])
                    else:
                        dp[j+1][k] = dp[j][k]
            res = min(total - max(max(dp)),res)
        return res
