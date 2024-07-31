class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        def rob(nums: List[int]) -> int:
            size = len(nums)
            if size == 1:
                return nums[0]

            first, second = nums[0], max(nums[0], nums[1])
            for i in range(2, size):
                first, second = second, max(first + nums[i], second)
            return second
        
        n = len(nums)
        ans = 0
        nums.sort()
        total = [nums[0]]

        for i in range(1, n):
            val = nums[i]
            if val == nums[i - 1]:
                total[-1] += val
            elif val == nums[i - 1] + 1:
                total.append(val)
            else:
                ans += rob(total)
                total = [val]
        
        ans += rob(total)
        return ans