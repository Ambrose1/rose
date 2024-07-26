impl Solution {
    pub fn count_good_strings(low: i32, high: i32, zero: i32, one: i32) -> i32 {
        const MOD: i32 = 1_000_000_007;
        let mut ans = 0;
        let mut f = vec![0; (high + 1) as usize];
        f[0] = 1;
        for i in 1..=high as usize {
            if i >= zero as usize {
                f[i] = (f[i] + f[i - zero as usize]) % MOD;
            }
            if i >= one as usize {
                f[i] = (f[i] + f[i - one as usize]) % MOD;
            }
            if i >= low as usize {
                ans = (ans + f[i]) % MOD;
            }
        }
        ans
    }
}