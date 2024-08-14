impl Solution {
    pub fn cherry_pickup(grid: Vec<Vec<i32>>) -> i32 {
        let m = grid.len();
        let n = grid[0].len();
        let mut f = vec![vec![-1; n]; n];
        let mut g = vec![vec![-1; n]; n];

        f[0][n - 1] = grid[0][0] + grid[0][n - 1];
        for i in 1..m {
            for j1 in 0..n {
                for j2 in 0..n {
                    let mut best = -1;
                    for dj1 in -1..=1 {
                        for dj2 in -1..=1 {
                            let dj1 = j1 as i32 + dj1;
                            let dj2 = j2 as i32 + dj2;
                            if dj1 >= 0 && dj1 < n as i32 && dj2 >= 0 && dj2 < n as i32 && f[dj1 as usize][dj2 as usize] != -1 {
                                best = best.max(f[dj1 as usize][dj2 as usize] + if j1 == j2 { grid[i][j1] } else { grid[i][j1] + grid[i][j2] });
                            }
                        }
                    }
                    g[j1][j2] = best;
                }
            }
            std::mem::swap(&mut f, &mut g);
        }

        let mut ans = 0;
        for j1 in 0..n {
            ans = ans.max(*f[j1].iter().max().unwrap_or(&0));
        }
        ans
    }
}

作者：力扣官方题解
链接：https://leetcode.cn/problems/cherry-pickup-ii/solutions/521172/zhai-ying-tao-ii-by-leetcode-solution-v2k5/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。