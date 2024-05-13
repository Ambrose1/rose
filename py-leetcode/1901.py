class Solution:
    def findPeakGrid(self, mat: List[List[int]]) -> List[int]:
        left, right = 0, len(mat) - 1
        while left < right:
            mid = (left + right) // 2
            mx = max(mat[mid])
            if mx > mat[mid + 1][mat[mid].index(mx)]:
                right = mid
            else:
                left = mid + 1
        i = left
        return [i, mat[i].index(max(mat[i]))]