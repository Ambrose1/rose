class Solution {
    func change(_ amount: Int, _ coins: [Int]) -> Int {
        if amount == 0 {
            return 1
        }
        // 初始化 dp 数组，dp[i] 表示凑成金额 i 所需的最少硬币数
        var dp = Array(repeating: 0, count: amount + 1)
        // 金额为 0 时不需要任何硬币，所以设置为 1
        dp[0] = 1
        
        // 遍历所有硬币
        for coin in coins {
            // 从硬币面额开始，到总金额
            if coin > amount {
                continue
            }
            for i in coin...amount {
                // 如果当前金额大于等于硬币面额，则更新 dp[i]
                if i >= coin {
                    // 这里应该是 dp[i] += dp[i - coin]，而不是 dp[i] = dp[i] + dp[i - coin]
                    dp[i] += dp[i - coin]
                }
            }
        }
        
        // 返回凑成总金额所需的最少硬币数
        // 如果 dp[amount] 为 0，表示无法凑成总金额
        return dp[amount]
    }
}