impl Solution {
    pub fn maximum_cost_substring(s: String, chars: String, vals: Vec<i32>) -> i32 {
         let mut va = [0;26];
         for i in 0..26 {
            va[i as usize] = i+1;
         }

        for (i,v) in chars.chars().enumerate() {
            va[v as usize - 'a' as usize] = vals[i]
        }

        let arr = s.chars().map(|c| va[c as usize - 'a' as usize]).collect();
        fn maxfunc(num: &Vec<i32>) -> i32 {
            let mut tmp = num[0];
            let mut res = num[0];
            for i in 1..num.len() {
                tmp = std::cmp::max(tmp + num[i], num[i]);
                if res < tmp {
                    res = tmp;
                }
            }
            res.max(0)
        }
        maxfunc(&arr)
    }
}