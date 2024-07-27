class Solution:
    def countTexts(self, pressedKeys: str) -> int:
        dp3 = [1,1,2,4]
        dp4 = [1,1,2,4]
        mod = 10**9+7
        for i in range(4, len(pressedKeys)+1):
            dp3.append((dp3[i-1] + dp3[i-2] + dp3[i-3])%mod)
            dp4.append((dp4[i-1] + dp4[i-2] + dp4[i-3] + dp4[i-4])%mod)
        cnt = 1
        res = 1
        for i in range(1,len(pressedKeys)):
            if (pressedKeys[i] == pressedKeys[i-1]):
                cnt+=1
            else:
                if (pressedKeys[i-1] in "79"):
                    res *= dp4[cnt]
                else:
                    res*=dp3[cnt]
                res %= mod
                cnt = 1
        if (pressedKeys[-1] in "79"):
            res *= dp4[cnt]
        else:
            res *= dp3[cnt]
        res%=mod
        return res
