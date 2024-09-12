use std::cmp::max;

const MOD: i64 = 10_i64.pow(9) - 7;
impl Solution {
    pub fn profitable_schemes(n: i32, min_profit: i32, group: Vec<i32>, profit: Vec<i32>) -> i32 {
        let m = profit.len();
        let mut dp = vec![vec![vec![0;(min_profit+1) as usize];(n+1) as usize];(m+1) as usize];
        dp[0][0][0] = 1;

        for i in 1..(m + 1) as usize {
            let member = group[i - 1] as usize;
            let profit_value = profit[i - 1] as usize;
            for j in 0..n as usize {
                for k in 0..min_profit as usize {
                    if j < member {
                        dp[i][j][k] = dp[i - 1][j][k];
                    } else {
                        dp[i][j][k] = (dp[i - 1][j][k] + dp[i - 1][j - member][max(0,(k as i32-min_profit)) as usize]) % MOD;
                    }
                }
            }
        }

        let mut count = 0;
        for i in 0..(n + 1) as usize {
            count += dp[m][i][min_profit as usize] % MOD;
        }

        count as i32
    }
}