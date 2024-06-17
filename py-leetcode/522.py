# 关键点在于子序列特殊，父序列一定特殊
class Solution:
    def findLUSlength(self, strs: List[str]) -> int:
        n = len(strs)
        
        def isSubSeq(str1, str2):
            m,n = len(str1), len(str2)
            x,y = 0,0
            while x < m and y < n:
                if str1[x] == str2[y]:
                    x+=1
                y+=1
            return x == m
        
        res = -1
        for i in range(n):
            check = True
            for j in range(n):
                if i != j and isSub(strs[i], strs[j]):
                    check = False
                    break
            if check:
                res = max(res, len(strs[i]))
        return res