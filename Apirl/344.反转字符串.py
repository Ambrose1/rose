#
# @lc app=leetcode.cn id=344 lang=python3
#
# [344] 反转字符串
#

# @lc code=start
class Solution:
    def reverseString(self, s: List[str]) -> None:
        """
        Do not return anything, modify s in-place instead.
        """
        st = 0
        e = len(s)-1
        while(st < e):
            self.swap(s, st, e)
            st+=1
            e-=1
        
    def swap(self,s,st,e):
        tmp = s[st]
        s[st] = s[e]
        s[e] = tmp
        pass
# @lc code=end

