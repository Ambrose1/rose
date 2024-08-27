class Solution {
    func minFallingPathSum(matrix: [[Int]]) -> Int {
        let n = matrix.count
        var dp = Array(repeating: 0, count: n)

        for i in 0..<n {
            dp[i] = matrix[0][i]
        }

        for i in 1..<n {
            var last = Array(repeating: 0, count: n)
            for j in 0..<n {
                if j == 0 {
                    last[j] = min(dp[j], dp[j+1])
                } else if j == n-1 {
                    last[j] = min(dp[j], dp[j-1])
                } else {
                    last[j] = min(dp[j], min(dp[j-1],dp[j+1]))
                }
                last[j] += matrix[i][j]
            }
            dp = last
        }
        return dp.min()!
    }
}