class Solution {
    func longestCommonSubsequence(_ text1: String, _ text2: String) -> Int {
        let m: Int = text1.count
        let n: Int = text2.count

        var dp:[[Int]] = Array(repeating: Array(repeating:0,count:n+1), count:m+1)

        for i in 1...m {
            for j in 1...n {
                let index1 = text1.index(text1.startIndex, offsetBy: i - 1)
                let index2 = text2.index(text2.startIndex, offsetBy: j - 1)
                if text1[index1] == text2[index2] {
                    dp[i][j] = dp[i-1][j-1] + 1
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                }
            }
        }
        return dp[m][n]
    }
}