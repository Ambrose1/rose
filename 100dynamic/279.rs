impl Solution {
    pub fn num_squares(n: i32) -> i32 {
        let mut dp:Vec<i32> = vec![std::i32::MAX; (n+1) as usize];
        dp[0] = 0;
         for i in 1..=n {
            let mut j = 1;
            while j * j <= i {
                dp[i as usize] = dp[i as usize].min(dp[(i - j * j) as usize] + 1);
                j += 1;
            }
        }
        dp[n as usize]

    }
}