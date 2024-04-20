/// 引用
use super::permutation_interface::PermutationInterface;

/// 结构体
pub struct Permutation;

/// 为结构体实现 trait
impl PermutationInterface for Permutation {
    /// 协议方法，可变数组引用作为参数传递，原地修改
    fn next_permutation(nums: &mut Vec<i32>) {
        let len = nums.len();
        let mut i = len - 2;

        // 逆序遍历，找到第一个逆序对 此处 i 是 usize 无符号数，0 - 1 会溢出为一个极大值，所以判断小于数组 range
        while i <= len - 1 && nums[i] >= nums[i + 1] {
            i -= 1;
        }

        // 判断方式同上
        if i <= len - 1 {
            // 找到左侧第一个比 i 数字小的数，（i 是第一个逆序对）交换位置
            let mut j = len - 1;
            while j > i && nums[j] <= nums[i] {
                j -= 1;
            }
            nums.swap(i,j);
        }

        // 调整 i 后面的数字，使其是最小的字典序。
        let mut left = i + 1;
        let mut right = len - 1;
        while left < right {
            nums.swap(left, right);
            left += 1;
            right -= 1;
        }
    }

    fn same_number(nums: Vec<i32>) -> i32 {
        let (mut fast, mut slow) = (nums[nums[0] as usize], nums[0]);
        while fast != slow {
            fast = nums[nums[fast as usize] as usize];
            slow = nums[slow as usize];
        }
        slow = 0;
        while slow != fast {
            slow = nums[slow as usize];
            fast = nums[fast as usize];
        }
        return slow;
    }

    fn find_root(n: i32, edges: Vec<Vec<i32>>) -> i32 {
        let mut st: u128 = 0;

        // 更新位，入度对应位更新为 1
        for i in &edges {
            st |= (1 << i[1]);
        }

        // 找没有入度的
        let mut r:i32 = -1;
        for j in 0..n {
            if st & (1 << j) == 0 {
                if r != -1 {
                    return -1;
                }
                r = j;
            }
        }
        r
    }
}

struct MyHashSet {
    hash_set: Vec<i32>
}


/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MyHashSet {

    fn new() -> Self {
        Self {
            hash_set : Vec::new()
        }
    }
    
    fn add(&mut self, key: i32) {
        let index = key / 32;
        let remainder = key % 32;
        if (index as usize) >= self.hash_set.len() {
            self.hash_set.resize(index as usize + 1, 0);
        }
        self.hash_set[index as usize] |= (1 << remainder);
    }
    
    fn remove(&mut self, key: i32) {
        let index = key / 32;
        let remainder = key % 32;
        if (index as usize) < self.hash_set.len() {
            self.hash_set[index as usize] &= !(1 << remainder);
        }
    }
    
    fn contains(&self, key: i32) -> bool {
        let index = key / 32;
        let remainder = key % 32;
        if (index as usize) < self.hash_set.len() {
            self.hash_set[index as usize] & (1 << remainder) != 0
        } else {
            false
        }
    }
}

/**
 * Your MyHashSet object will be instantiated and called as such:
 * let obj = MyHashSet::new();
 * obj.add(key);
 * obj.remove(key);
 * let ret_3: bool = obj.contains(key);
 */