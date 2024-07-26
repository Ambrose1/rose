class Solution:
    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:
        MOD = 1_000_000_007
        f = [1] + [0] * high  # f[i] 表示构造长为 i 的字符串的方案数
        for i in range(1, high + 1):
            if i >= zero: f[i] = (f[i] + f[i - zero]) % MOD
            if i >= one:  f[i] = (f[i] + f[i - one]) % MOD
        return sum(f[low:]) % MOD