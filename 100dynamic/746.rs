use std::cmp;
impl Solution {
    pub fn min_cost_climbing_stairs(cost: Vec<i32>) -> i32 {
        let mut dp0: i32 = 0;
        let mut dp1: i32 = 0;
        let mut dp: i32 = 0;

        for i in 2..cost.len()+1 {
            dp = cmp::min(dp0 + cost[i as usize - 2], dp1 + cost[i as usize - 1]);
            dp0 = dp1;
            dp1 = dp;
        }
        dp1
    }
}