mod permutation;

use permutation::{Permutation, PermutationInterface};

fn main() {
    let mut nums = vec![1, 2, 3];
    Permutation::next_permutation(&mut nums);
    println!("Hello, world!: {:?}", &nums);
}
