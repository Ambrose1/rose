mod permutation;

use permutation::{Permutation, PermutationInterface};

fn main() {
    let mut nums = vec![1, 2, 3];
    Permutation::next_permutation(&mut nums);
    println!("Hello, world!: {:?}", &nums);

    let same_number_num = vec![1,2,4,3,3,3];
    let result = Permutation::same_number(same_number_num);
    println!("相同的数：{}",result);
}
