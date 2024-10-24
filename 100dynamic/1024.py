class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        count,j = 0,0
        set_a = {'a','e','i','o','u'}
        tmp = [0] * len(s)
        if (s[0] in set_a):
            tmp[0] = 1
        for i in range(1,len(s)):
            if (s[i] in set_a):
                tmp[i] += tmp[i-1] + 1
            else:
                tmp[i] = tmp[i-1]
        count = tmp[k-1]
        print (tmp)
        for i in range(k,len(s)):
            count = max(tmp[i] - tmp[i-k],count)
        return count

        