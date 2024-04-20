// 约定接口协议
pub trait PermutationInterface {
    fn next_permutation(nums: &mut Vec<i32>);
    fn same_number(nums: Vec<i32>) -> i32;
    fn find_root(n: i32, edges: Vec<Vec<i32>>) -> i32;
}