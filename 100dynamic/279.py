class Solution:
    def numSquares(self, n: int) -> int:
        if n <= 1:
            return 1
         # Initialize dp array with infinity values
        dp = [float('inf')] * (n + 1)
        dp[0] = 0  # Base case: 0 perfect squares needed to make 0
        
        # Fill the dp array
        for i in range(1, n + 1):
            # Start from the square root of i and go down to 1
            for j in range(int(i**0.5), 0, -1):
                dp[i] = min(dp[i], dp[i - j*j] + 1)
        
        return dp[n]