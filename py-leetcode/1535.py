class Solution:
    def getWinner(self, arr: List[int], k: int) -> int:
        n = len(arr)
        curmax, currk = arr[0], 0
        for i in range(1, n):
            if currk == k:
                return curmax
            if curmax > arr[i]:
                currk += 1
            else:
                currk = 1
                curmax = arr[i]
        return curmax