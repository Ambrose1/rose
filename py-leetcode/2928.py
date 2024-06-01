# 排列组合
# 给你两个正整数 n 和 limit。
# 请你将 n 颗糖果分给 3 位小朋友，确保没有任何小朋友得到超过 limit 颗糖果，请你返回满足此条件下的 总方案数。

class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        return self.cal(n + 2) - 3 * self.cal(n - limit + 1) + 3 * self.cal(n -(limit + 1) * 2 + 2) - self.cal(n - 3 *(limit + 1) +2)

    def cal(self, x):
        if (x < 0):
            return 0
        return int(x  * (x - 1) / 2)
    