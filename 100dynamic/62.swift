class Solution {
    func uniquePaths(_ m: Int, _ n: Int) -> Int {
        var dp = Array(repeating:0, count: n)
        dp[0] = 1

        for i in 0..<m {
            for j in 1..<n {
                dp[j] = dp[j] + dp[j-1]
            }
        }
        return dp[n-1]
    }
}