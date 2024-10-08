class Solution:
    def distributeCookies(self, cookies: List[int], k: int) -> int:
        m = 1 << len(cookies)
        s = [0] * m
        for i,v in enumerate(cookies):
            bit = 1 << i
            for j in range(bit):
                s[bit | j] = s[j] + v
        f = s.copy()
        for _ in range(1, k):
            for j in range(m-1,0, -1):
                t = j
                while t:
                    v = f[j^t]
                    if s[t] > v: v = s[t]
                    if v < f[j]: f[j] = v
                    t = (t - 1) & j
        return f[-1]
        