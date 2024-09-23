class Solution {
    func coinChange(_ coins: [Int], _ amount: Int) -> Int {
        // 初始化 dp 数组，长度为 amount+1，初始值设为一个大数表示无法组成
        var dp = Array(repeating: Int.max, count: amount + 1)
        // 金额为 0 时不需要任何硬币
        dp[0] = 0

        // 遍历所有硬币
        for coin in coins {
            // 从硬币值开始，更新 dp 数组
            if amount < coin {
                continue
            }
            for i in coin...amount {
                // 如果当前金额减去硬币值的金额可以组成，并且加上当前硬币后更优
                if dp[i - coin] != Int.max {
                    dp[i] = min(dp[i], dp[i - coin] + 1)
                }
            }
        }

        // 如果 dp[amount] 还是初始值，表示无法组成该金额
        return dp[amount] == Int.max ? -1 : dp[amount]
    }
}

let s: Solution = Solution()
let v = s.coinChange([1],0)
print("cc",v)
