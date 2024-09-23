impl Solution {
    pub fn coin_change(coins: Vec<i32>, amount: i32) -> i32 {
        if amount == 0 {
            return 0;
        }

        let mut dp = vec![std::i32::MAX; (amount + 1) as usize];
        dp[0] = 0;

        for &coin in &coins {
            for i in coin..=amount {
                if dp[(i - coin) as usize] != std::i32::MAX {
                    dp[i as usize] = dp[i as usize].min(dp[(i - coin) as usize] + 1);
                }
            }
        }

        if dp[amount as usize] == std::i32::MAX {
            -1
        } else {
            dp[amount as usize]
        }
    }
}