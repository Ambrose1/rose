def maxDivScore(self, nums: List[int], divisors: List[int]) -> int:
        divisors_n = list(set(divisors))
        ctn = -1
        ans = 0
        for i in divisors_n:
            tmp = 0
            for j in nums:
                if j % i == 0:
                    tmp += 1
            
            if tmp > ctn or (tmp == ctn and i < ans):
                ans = i
                ctn = tmp
        return ans