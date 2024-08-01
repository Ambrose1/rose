class Solution:
    def countHousePlacements(self, n: int) -> int:
        if n==1:
            return 4
        if n== 2:
            return 9
        f,s = 2,3
        mod = 10**9 + 7
        for i in range(2,n):
            tmp = s
            s = (f + s)%mod
            f = tmp
        return s*s%mod