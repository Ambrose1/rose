impl Solution {
    pub fn max_sub_array(nums: Vec<i32>) -> i32 {
        let mut tmp: i32 = nums[0];
        let mut res: i32 = tmp;
        let n:usize = nums.len();
        for i in 1..n {
            tmp = std::cmp::max(tmp + nums[i as usize], nums[i as usize]);
            if tmp > res {
                res = tmp;
            }
        }
        res
    }
}