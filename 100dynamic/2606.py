class Solution:
    def maximumCostSubstring(self, s: str, chars: str, vals: List[int]) -> int:
        va = [i for i in range(1,27)]

        for i in range(len(chars)):
            ch = chars[i]
            va[ord(ch) - ord('a')] = vals[i]
        arr = []
        for i in s:
            arr.append(va[ord(i) - ord('a')])
        
        def maxSubArray(nums: List[int]) -> int:
            n = len(nums)
            if (n == 1):
                return nums[0]
            tmp = nums[0]
            res = tmp
            for i in range(1,n):
                tmp = max(tmp + nums[i], nums[i])
                if tmp > res:
                    res = tmp
            return res
        res = maxSubArray(arr)
        return max(0,res)
