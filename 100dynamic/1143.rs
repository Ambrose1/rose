impl Solution {
    pub fn longest_common_subsequence(text1: String, text2: String) -> i32 {
        let m = text1.len();
        let n = text2.len();

        // 初始化 dp 数组，第一行和第一列为 0
        let mut dp = vec![vec![0; n + 1]; m + 1];

        // 从 1 开始遍历，因为第一行和第一列已经初始化为 0
        for i in 1..=m {
            for j in 1..=n {
                if text1.as_bytes()[i - 1] == text2.as_bytes()[j - 1] {
                    // 如果当前字符匹配，增加对角线上的值
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // 如果当前字符不匹配，取上方或左方的最大值
                    dp[i][j] = dp[i - 1][j].max(dp[i][j - 1]);
                }
            }
        }

        // 返回 dp 数组的最后一个元素，即为最长公共子序列的长度
        dp[m][n]
    }
}