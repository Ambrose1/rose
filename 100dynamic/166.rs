impl Solution {
    pub fn jewellery_value(frame: Vec<Vec<i32>>) -> i32 {
        let cols: usize = frame.len();
        let rows: usize = frame[0].len();

        let mut dp = vec![vec![0;rows];cols];
        dp[0][0] = frame[0][0];
        for x in 1..cols {
            dp[x][0] = dp[x-1][0] + frame[x][0];
        }
        for y in 1..rows {
            dp[0][y] = dp[0][y-1] + frame[0][y];
        }

        for i in 1..cols {
            for j in 1..rows {
                let val: i32 = frame[i][j];
                dp[i][j] = dp[i-1][j].max(dp[i][j-1]) + val;
            }
        }
        dp[cols-1][rows-1]
    }
}