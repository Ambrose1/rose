class Solution {
    func numSquares(_ n: Int) -> Int {
        var dp:[Int] = Array(repeating:Int.max, count:n+1)
        dp[0] = 0
        for i in 1...n {
            for j in stride(from: Int(sqrt(Double(i))), through: 0, by: -1) {
                dp[i] = min(dp[i - j*j] + 1, dp[i])
            }
        }
        return dp[n]
    }
}