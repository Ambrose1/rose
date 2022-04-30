#
# @lc app=leetcode.cn id=125 lang=python3
#
# [125] 验证回文串
#

# @lc code=start
class Solution:
    def isPalindrome(self, s: str) -> bool:
        s = "".join(filter(str.isalnum,s)).lower()
        print(s)
        print(reversed(s))
        n = len(s)-1
        i = 0
        while(i<n):
            if s[i] != s[n] :
                return False
            i+=1
            n-=1
        return True

# @lc code=end

