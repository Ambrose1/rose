class Solution:
    def longestEqualSubarray(self, nums: List[int], k: int) -> int:
        cur,n,ans = 0, len(nums),0
        cnt = {}
        for i in range(n):
            if nums[i] in cnt:
                cnt[nums[i]] += 1
            else:
                cnt[nums[i]] = 1
            while i - cur + 1 - cnt[nums[cur]] > k:
                cnt[nums[cur]] -= 1
                cur+=1
            ans = max(ans, cnt[nums[i]])
        return ans
