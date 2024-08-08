impl Solution {
    pub fn unique_paths(m: i32, n: i32) -> i32 {
        let mut dp: Vec<i32> = vec![0;n as usize];
        dp[0] = 1;

        for i in 0..m {
            for j in 1..n {
                dp[j as usize] = dp[j as usize] + dp[(j-1) as usize];
            }
        }
        dp[(n-1) as usize]
    }
}