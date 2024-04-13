use super::permutation_interface::PermutationInterface;

pub struct Permutation;

impl PermutationInterface for  Permutation {

    fn next_permutation(nums: &mut Vec<i32>) {
        let len = nums.len();
        let mut i = len - 2;

        while i <= len - 1 && nums[i] >= nums[i + 1] {
            i -= 1;
        }

        if i <= len - 1 {
            let mut j = len - 1;
            while j > i && nums[j] <= nums[i] {
                j -= 1;
            }
            nums.swap(i,j);
        }

        let mut left = i + 1;
        let mut right = len - 1;
        while left < right {
            nums.swap(left, right);
            left += 1;
            right -= 1;
        }
    }
}