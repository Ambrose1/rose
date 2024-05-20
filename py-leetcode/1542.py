class Solution:
    def longestAwesome(self, s: str) -> int:
        n = len(s)
        prefix = {0 : -1}
        ans, seq = 0,0

        for i in range(n):
            index = ord(s[i]) - ord('0')
            seq ^= (1 << index)

            if seq in prefix:
                ans = max(ans, i - prefix[seq])
            else:
                prefix[seq] = i
            for k in range(10):
                if seq ^ (1 << k) in prefix:
                    ans = max(ans, i - prefix[seq ^ (1 << k)])
        return ans

