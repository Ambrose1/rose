impl Solution {
    pub fn unique_paths_with_obstacles(obstacle_grid: Vec<Vec<i32>>) -> i32 {
        let m: usize = obstacle_grid.len();
        let n: usize = obstacle_grid[0].len();

        let mut dp:Vec<i32> = vec![0;n];
        for i in 0..n as usize {
            if obstacle_grid[0][i] == 0 {
                dp[i] = 1;
            } else {
                break;
            }
        }

        for i in 1..m {
            for j in 0..n {
                if obstacle_grid[i][j] == 1 {
                    dp[j] = 0;
                } else {
                    if j > 0 {
                        dp[j] += dp[j-1]
                    }
                }
            }
        }
        dp[n-1]
    }
}