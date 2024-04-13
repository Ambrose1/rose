// permutation/mod.rs

// 导入子模块
mod permutation_interface;
mod permutation;

// 重新导出子模块中的内容，使其对外可见
pub use permutation_interface::PermutationInterface;
pub use permutation::Permutation;
