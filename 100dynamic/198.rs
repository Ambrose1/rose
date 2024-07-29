impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let n:usize = nums.len();
        if n == 1 {
            return nums[0];
        }
        let mut dp = vec![0;n];
        dp[0] = nums[0];
        dp[1] = std::cmp::max(nums[0],nums[1]);
        for i in 2..n {
            dp[i] = std::cmp::max(dp[i-1], dp[i-2] + nums[i]);
        }
        dp[n-1]
    }
}