impl Solution {
    pub fn count_house_placements(n: i32) -> i32 {
        if n == 2 {
            return 9;
        }
        if n== 1{
            return 4;
        }
        let mut f:i32 = 2;
        let mut s:i32 = 3;
        let mut tmp = s;
        let m:i32 = 1_000_000_007;
        
        for i in 2..n {
            tmp = s;
            s = (f + s)%m;
            f = tmp;
        }
        let res:i64 = ((s%m) as i64) *((s%m) as i64) % (m as i64);
        res as i32
    }
}