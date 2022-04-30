#
# @lc app=leetcode.cn id=2108 lang=python3
#
# [2108] 找出数组中的第一个回文字符串
#

# @lc code=start
class Solution:

    def isHuiWen(self,word):
        n = len(word)-1
        st = 0
        while(st < n):
            if (word[st] != word[n]):
                return False
            st+=1
            n-=1
        return True
    def firstPalindrome(self, words: List[str]) -> str:
        for item in words:
            if(self.isHuiWen(item)):
                return item
        return ""
# @lc code=end

