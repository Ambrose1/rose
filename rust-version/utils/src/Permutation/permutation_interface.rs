// 约定接口协议
pub trait PermutationInterface {
    fn next_permutation(nums: &mut Vec<i32>);
    fn same_number(nums: Vec<i32>) -> i32;
}